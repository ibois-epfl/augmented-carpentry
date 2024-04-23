import Rhino
import Rhino.Geometry as rg

import ACPy.ac_util

# note the tolerance had to be doubled to avoid boolean difference errors
TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance * 2
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
        :return tuple: A tuple containing the AABB, holes and cuts breps (and extra breps for debugging)
    """
    holes_b = []
    cuts_b = []
    mix_b = []
    bbox_b = None
    __debugger__ = []  # extra breps that are not holes or cuts for debugging
    ##########################################################################
    # -- get negatives between beam and AABB --
    ##########################################################################
    bbox = beam.GetBoundingBox(True)
    # the AABB is inflated to avoid boolean difference errors
    bbox.Inflate(0, -TOL_DOC, -TOL_DOC)
    ACIM.add_bbox(beam_name, bbox.GetCorners())

    bbox_b = bbox.ToBrep()
    breps = rg.Brep.CreateBooleanDifference(bbox_b, beam, TOL_DOC)
    if breps is None or len(breps) == 0:
        raise ValueError("No breps found after boolean difference. Exiting...")
    for b in breps:
        if not b.IsValid:
            b.Repair(TOL_DOC)
            if not b.IsValid:
                raise ValueError(f"Brep is not valid after boolean difference with AABB for {beam_name}. Exiting...")
                return

    ##########################################################################
    # -- detect holes, cuts (and mixes) --
    ##########################################################################
    # parse holes, cuts and mix
    is_hole = False
    is_cut = False
    is_mix = False
    for b in breps:
        # __debugger__.append(b)
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
        if flat_faces_b is None:
            raise ValueError(f"No breps found after boolean union for {beam_name} Exiting...")
            return
        flat_faces_b = [f_b.CapPlanarHoles(TOL_DOC) for f_b in flat_faces_b]

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

    return bbox_b, holes_b, cuts_b, __debugger__

