import Rhino as rc
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs
import scriptcontext as sc

def get_brep_face_center(brep_face):
    u_domain = brep_face.Domain(0)
    v_domain = brep_face.Domain(1)
    u_center = (u_domain.Min + u_domain.Max) / 2.0
    v_center = (v_domain.Min + v_domain.Max) / 2.0
    center_point = brep_face.PointAt(u_center, v_center)
    return center_point

def explode_brep(brep):
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

def get_data_from_brep(brep):
    """
        Get the data to export from a cylinder
        :param brep: the brep cylinder representing the hole
        :return: the data
    """

    # sc.doc.Objects.AddBrep(brep)  # TODO: debug

    # extract the curves from the brep
    curves = brep.DuplicateEdgeCurves(True)

    brep_faces = explode_brep(brep)
    print(len(brep_faces))

    for face in brep_faces:
        sc.doc.Objects.AddBrep(face)  # TODO: debug


    # add to document
    for curve in curves:
        sc.doc.Objects.AddCurve(curve)