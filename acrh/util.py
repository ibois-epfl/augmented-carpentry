import Rhino as rc
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs
import scriptcontext as sc

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

def get_crv_circle_center(crv):
    bbox = crv.GetBoundingBox(True)
    bbox_b = bbox.ToBrep()
    center_point = bbox_b.GetBoundingBox(True).Center
    return center_point

def is_pt_unique_in_dict(pt, pt_dict):
    is_unique = True
    for pt_dict in pt_dict.keys():
        X_a = round(pt.X, 3)
        Y_a = round(pt.Y, 3)
        Z_a = round(pt.Z, 3)

        X_b = round(pt_dict.X, 3)
        Y_b = round(pt_dict.Y, 3)
        Z_b = round(pt_dict.Z, 3)

        if X_a == X_b and Y_a == Y_b and Z_a == Z_b:
            is_unique = False
            break
    return is_unique

def is_pt_unique_in_list(pt, list):
    is_unique = True
    for pt_list in list:
        X_a = round(pt.X, 3)
        Y_a = round(pt.Y, 3)
        Z_a = round(pt.Z, 3)

        X_b = round(pt_list.X, 3)
        Y_b = round(pt_list.Y, 3)
        Z_b = round(pt_list.Z, 3)

        if X_a == X_b and Y_a == Y_b and Z_a == Z_b:
            is_unique = False
            break
    return is_unique

def detect_idx_pt_in_list(pt, list):
    """ Detect if the point exists, and if so, return the index """
    idx = -1
    for pt_list in list:
        idx += 1
        X_a = round(pt.X, 3)
        Y_a = round(pt.Y, 3)
        Z_a = round(pt.Z, 3)

        X_b = round(pt_list.X, 3)
        Y_b = round(pt_list.Y, 3)
        Z_b = round(pt_list.Z, 3)

        if X_a == X_b and Y_a == Y_b and Z_a == Z_b:
            return idx
    return idx
