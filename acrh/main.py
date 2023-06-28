import rhinoscriptsyntax as rs
import Rhino as rc
import scriptcontext as sc
import Rhino.Geometry as rg
import datetime as dt

import log
import acim
import hole

import visual_debug as vd

def pln_2_pln_world_transform(brep):
    """ Transform a brep to the world plane """
    log.info("Computing Oriented Bounding Boxes...")

    # find the longest edge of the brep
    edges = brep.Edges
    longest_edge = None
    longest_edge_length = 0
    for edge in edges:
        if edge.GetLength() > longest_edge_length:
            longest_edge_length = edge.GetLength()
            longest_edge = edge
    
    # get face of the longest edge
    face_indices = longest_edge.AdjacentFaces()
    faces = [brep.Faces[face_index] for face_index in face_indices]

    log.info("Found " + str(len(faces)) + " faces for longest edge.")

    # get the biggest face
    biggest_face = None
    biggest_face_area = 0
    for face in faces:
        if rg.AreaMassProperties.Compute(face).Area > biggest_face_area:
            biggest_face_area = rg.AreaMassProperties.Compute(face).Area
            biggest_face = face
    
    # get the plane of the biggest face
    if biggest_face.TryGetPlane()[0] is False:
        log.error("Could not find plane for longest edge. Exiting...")
        return
    plane_src = biggest_face.TryGetPlane()[1]
    log.info("Found plane for longest edge: " + str(plane_src))
    plane_tgt = rc.Geometry.Plane.WorldXY

    # plane to plane transformation
    plane_to_world = rc.Geometry.Transform.PlaneToPlane(plane_src, plane_tgt)
    brep.Transform(plane_to_world)

def distinguish_holes_cuts(breps):
    """ 
        Analyse the result breps from the boolean difference operation
        and distinguish between holes and cuts
    """
    is_hole = False
    is_cut = False
    holes_b = []
    cuts_b = []

    for b in breps:
        is_cut = True
        for f in b.Faces:
            f_brep = f.ToBrep()
            f = f_brep.Faces[0]
            if not f.IsPlanar():
                is_hole = True
                continue
        if is_hole:
            holes_b.append(b)
        elif is_cut:
            cuts_b.append(b)

        is_hole = False
        is_cut = False

    return holes_b, cuts_b

def main():

    vd.set_on()
    print(vd.__IS_VDEBUG__)

    log.info(".acim exporter started")

    rh_doc_path = rs.DocumentPath()
    timestamp = dt.datetime.now().strftime("%Y%m%d_%H%M%S")
    acim_path = rh_doc_path + timestamp
    log.info("Creating ACIM file at: " + acim_path)
    ACIM = acim.ACIM(acim_path)

    pieces = rs.GetObjects("Select pieces to be exported", rs.filter.polysurface, preselect=True)
    if not pieces:
        log.error("No pieces selected. Exiting...")
        return

    for p_GUID in pieces:
        log.info("Processing piece: " + str(p_GUID))
        ACIM.add_timber(str(p_GUID))
        ACIM.add_timber_state(str(p_GUID), 0)
        brep = rs.coercebrep(p_GUID)
        
        # transform to world plane
        pln_2_pln_world_transform(brep)

        # compute the bounding box
        bbox = brep.GetBoundingBox(True)
        bbox_b = bbox.ToBrep()
        ACIM.add_bbox(str(p_GUID), bbox.GetCorners())

        # boolean difference between the bounding box and the brep transformed
        brep_result = rc.Geometry.Brep.CreateBooleanDifference(bbox_b, brep, sc.doc.ModelAbsoluteTolerance)
        if brep_result is None or len(brep_result) == 0:
            log.error("No breps found after boolean difference. Exiting...")
            return

        # FIXME: it is not working for holes on cut for now
        # get holes and cuts breps
        holes_b, cuts_b = distinguish_holes_cuts(brep_result)

        # analyse and loading holes and cuts into .acim
        for hole_b in holes_b:
            log.info("Processing hole: " + str(hole_b))
            hole.parse_data_from_brep(ACIM, str(p_GUID), hole_b, bbox_b)

        sc.doc.Views.Redraw()
    ACIM.dump_data()

if __name__ == '__main__':
    main()