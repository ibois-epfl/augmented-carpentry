import Rhino as rc
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs
import scriptcontext as sc
import random

import log
import acim

# def _get_radius_from_brep(brep):
#     face = brep.Faces[0]
#     face_brep = face.DuplicateFace(False)
#     if face_brep.IsSurface:
#         #get the radius of the cylinder
        


def _get_single_face_brep_center(brep):
    bbox = brep.GetBoundingBox(True)
    bbox_b = bbox.ToBrep()
    center_point = bbox_b.GetBoundingBox(True).Center
    return center_point

def _explode_brep(brep):
    exploded_objects = []
    if brep.IsSolid:
        for face in brep.Faces:
            face_brep = face.DuplicateFace(False)
            if face_brep:
                exploded_objects.append(face_brep)
    else:
        for face in brep.Faces:
            face_brep = face.DuplicateFace(False)
            if face_brep:
                exploded_objects.append(face_brep)
    return exploded_objects

def get_data_from_brep(ACIM, p_GUID, cylinder_b, bbox_b):
    """
        Get the data to export from a cylinder
        :param brep: the brep cylinder representing the hole
        :return: the data
    """
    bbox_faces_b = _explode_brep(bbox_b)
    cylinder_faces_b = _explode_brep(cylinder_b)
    log.info("cylinder_faces_b: " + str(len(cylinder_faces_b)))

    # sc.doc.Objects.AddBrep(cylinder_b)  # TODO: debug
    # >>>> simple hole
    is_simple_hole = False
    if len(cylinder_faces_b) == 3:
        is_simple_hole = True
        log.info("2-points hole detected")

    acim_centers = {}
    for face in cylinder_faces_b:
        # discard the round surfaces
        if not face.Faces[0].IsPlanar():
            continue

        face_guid = sc.doc.Objects.AddBrep(face)  # TODO: debug

        face_center = _get_single_face_brep_center(face)
        log.info("face_center: " + str(face_center))
        # pt_guid = rs.AddPoint(face_center)  # TODO: debug

        # if the center is inside the bbox, continue
        is_on_face = False
        if bbox_b.IsPointInside(face_center, sc.doc.ModelAbsoluteTolerance, True):
            acim_centers[face_center] = is_on_face
            continue

        point_surf_dist = rs.IsPointOnSurface(face, face_center)
        log.info("point_surf_dist: " + str(point_surf_dist))

        # PROP: get if the point is on the bbox surface
        if point_surf_dist:
            is_on_face = True
            log.info("face_center is on face")
            rs.ObjectColor(face_guid, (255,0,255))  # TODO: debug

        acim_centers[face_center] = is_on_face

    centers_len = len(acim_centers)
    if centers_len == 0:
        log.error("No center found for the hole. Exiting...")
        return
    if centers_len == 1:
        log.info("Single center found for the hole. Exiting...")
        return
    if centers_len == 2:
        log.info("Simple 2-points hole detected")

        # detect which point is start and end
        start_pt = rg.Point3d(0,0,0)
        end_pt = rg.Point3d(0,0,0)
        is_start_pt_accessible = False
        is_end_pt_accessible = False
        if acim_centers.values()[0]:
            start_pt = acim_centers.keys()[0]
            end_pt = acim_centers.keys()[1]
            is_start_pt_accessible = acim_centers.values()[0]
            is_end_pt_accessible = acim_centers.values()[1]
        else:
            start_pt = acim_centers.keys()[1]
            end_pt = acim_centers.keys()[0]
            is_start_pt_accessible = acim_centers.values()[1]
            is_end_pt_accessible = acim_centers.values()[0]

        # get the radius
        radius = 0
        for face in cylinder_faces_b:
            if face.Faces[0].IsPlanar():
                face_curves = face.DuplicateEdgeCurves(True)
                face_crv = face_curves[0]
                sc.doc.Objects.AddCurve(face_crv)  # TODO: DEBUG
                pt_base = face_crv.PointAtStart
                pt_base_GUID = sc.doc.Objects.AddPoint(pt_base)  # TODO: DEBUG
                rs.ObjectColor(pt_base_GUID, (255,0,0))  # TODO: debug
                axis_ln = rg.Line(start_pt, end_pt)
                sc.doc.Objects.AddLine(axis_ln)  # TODO: DEBUG
                radius = axis_ln.DistanceTo(pt_base, False)
                radius = round(radius, 3)
                log.info("radius: " + str(radius))
                break

        # store in acim
        ACIM.add_hole(p_GUID,
                    start_pt,
                    end_pt,
                    is_start_pt_accessible,
                    is_end_pt_accessible,
                    radius)
    if centers_len > 2:
        log.info("Complex hole detected")
        holes = []
        
        # get the two farthest points by comparing the distance between each other
        dists = []
        extreme_pts = []
        for i in range(0, centers_len):
            for j in range(i+1, centers_len):
                pt1 = acim_centers.keys()[i]
                pt2 = acim_centers.keys()[j]
                # ln = rg.Line(pt1, pt2)
                # ln_guid = sc.doc.Objects.AddLine(ln)  # TODO: DEBUG
                # # assign random color
                # color = (random.randint(0,255),
                #          random.randint(0,255),
                #          random.randint(0,255))  # TODO: debug
                # rs.ObjectColor(ln_guid, color)  # TODO: debug
                dist = pt1.DistanceTo(pt2)
                # if dist is the biggest in dists
                dists.append(dist)
                if dist >= max(dists) or len(dists) == 0:
                    extreme_pts = [i, j]

        # # sc.doc.Objects.AddPoint(extreme_pts[0])  # TODO: DEBUG
        # # sc.doc.Objects.AddPoint(extreme_pts[1])  # TODO: DEBUG
        extreme_pts = [acim_centers.keys()[extreme_pts[0]],
                       acim_centers.keys()[extreme_pts[1]]]
        longest_ln = rg.Line(extreme_pts[0], extreme_pts[1])
        longest_crv = longest_ln.ToNurbsCurve()

        centers_lst_reorder = list(acim_centers.keys())
        centers_lst_reorder.sort(key=lambda x: extreme_pts[0].DistanceTo(x))

        #create segments
        hole_axis_ln = []
        for i in range(0, centers_len-1):
            pt1 = centers_lst_reorder[i]
            pt2 = centers_lst_reorder[i+1]
            ln = rg.Line(pt1, pt2)
            sc.doc.Objects.AddLine(ln)  # TODO: debug
            hole_axis_ln.append(ln)

        # >>>>>>>>>>>>>>>>>>>>>>>
        # for axis_ln in hole_axis_ln:
        #     # get the radius
        #     radius = 0
        #     for face in cylinder_faces_b:
        #         if face.Faces[0].IsPlanar():
        #             face_curves = face.DuplicateEdgeCurves(True)
        #             if face_curves.__len__() > 0:
        #                 # get the smallest curve

        #             face_crv = face_curves[0]






        

