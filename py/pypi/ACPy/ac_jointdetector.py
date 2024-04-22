import Rhino
import Rhino.Geometry as rg

import ACPy.ac_util

TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIVE_DOC = Rhino.RhinoDoc.ActiveDoc

def distinguish_holes_cuts(beam : rg.Brep,
                           ACIM, 
                           beam_name : str):
    """ 
        Analyse the result breps from the boolean difference operation
        and distinguish between holes and cuts

        :param beam: The brep object representing the beam
        :param ACIM: The ACIM object to export xml
        :param beam_name: The name of the beam
        :return tuple: A tuple containing the AABB, holes and cuts breps
    """
    ##########################################################################
    # -- get negatives between beam and AABB --
    ##########################################################################
    bbox = beam.GetBoundingBox(True)
    bbox_b = bbox.ToBrep()
    ACIM.add_bbox(beam_name, bbox.GetCorners())

    breps = rg.Brep.CreateBooleanDifference(bbox.ToBrep(), beam, ACTIVE_DOC.ModelAbsoluteTolerance)
    if breps is None or len(breps) == 0:
        raise ValueError("No breps found after boolean difference. Exiting...")

    ##########################################################################
    # -- detect holes, cuts (and mixes) --
    ##########################################################################
    is_hole = False
    is_cut = False
    is_mix = False
    holes_b = []
    cuts_b = []
    mix_b = []

    # parse holes, cuts and mix
    for b in breps:
        is_cut = True
        for f in b.Faces:
            f_brep = f.ToBrep()
            f = f_brep.Faces[0]
            if not f.IsPlanar():
                is_cut = False
                is_hole = True
                b_faces = ACPy.ac_util.explode_brep(b)
                for b_face in b_faces:
                    if b_face.Faces[0].IsPlanar():
                        b_face_edges = b_face.Edges
                        for b_face_edge in b_face_edges:
                            if not b_face_edge.IsClosed:
                                is_mix = True
                                is_hole = False
                                break
                        if is_mix:
                            break
                break

        if is_hole:
            holes_b.append(b)
        elif is_cut: 
            cuts_b.append(b)
        elif is_mix:
            mix_b.append(b)

        is_hole = False
        is_cut = False
        is_mix = False
    
    # deal with mix
    candidate_cuts = []
    candidate_holes = []
    for b in mix_b:
        # -- algorithm draft --
        # (1) explode
        # (2) seperate in tow list flat surfaces (cuts + cylinder's bases) and non flat surfaces (cylinders)
        # (3) cap each object in both lists
        # (4) boolunion every object in both lists
        # (5) check if closed, if it is 
        # ----------------------
        # (1) explode
        faces_b = ACPy.ac_util.explode_brep(b)

        # (2) seperate in tow list flat surfaces (cuts + cylinder's bases) and non flat surfaces (cylinders)
        flat_faces_b = []
        non_flat_faces_b = []
        for f_b in faces_b:
            if f_b.Faces[0].IsPlanar():
                flat_faces_b.append(f_b)
            else:
                non_flat_faces_b.append(f_b)
  
        # (*) cap the cylinders
        non_flat_faces_b = [f_b.CapPlanarHoles(TOL_DOC) for f_b in non_flat_faces_b]
        
        # (4) boolunion every object in both lists
        flat_faces_b = rg.Brep.CreateBooleanUnion(flat_faces_b, TOL_DOC)
        non_flat_faces_b = rg.Brep.CreateBooleanUnion(non_flat_faces_b, TOL_DOC)

        # (3) cap candidate cuts
        flat_faces_b = [f_b.CapPlanarHoles(TOL_DOC) for f_b in flat_faces_b]
        # non_flat_faces_b = [f_b.CapPlanarHoles(TOL_DOC) for f_b in non_flat_faces_b]

        # (*) merge all coplanar faces in breps cut candidates
        for f_b in flat_faces_b:
            if f_b is not None:
                f_b.MergeCoplanarFaces(TOL_DOC)

        # (5) check if closed, if it is add to cuts, if not add to holes
        for f_b in flat_faces_b:
            if f_b is not None:
                if f_b.IsSolid:
                    cuts_b.append(f_b)
        for f_b in non_flat_faces_b:
            if f_b is not None:
                if f_b.IsSolid:
                    holes_b.append(f_b)

    return bbox_b, holes_b, cuts_b

