#! python3
""" Tester python for the pypi module """


import Rhino
import Rhino.Geometry as rg

TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIVE_DOC = Rhino.RhinoDoc.ActiveDoc

import ACPy
import ACPy.ac_acim
import ACPy.ac_transformations
import ACPy.ac_jointdetector
import ACPy.ac_util
import ACPy.ac_hole
import ACPy.ac_cut

if __name__ == "__main__":
    print(f"ACPyApp v{ACPy.__version__}")

    # list to output visual debug information
    debug_holes = []
    debug_cuts = []
    debug_bbox = None

    for idx, i_beam in enumerate(i_beams):
        # retrieve the name of the beam from document
        beam_name = ACPy.ac_util.get_brep_object_name(i_beam, i_GUIDs[idx])
        ACIM = ACPy.ac_acim.ACIM(out_dir=i_acim_path, 
                                 out_name=beam_name)
        ACIM.add_timber(beam_name)

        # bring the beam to the XY axis for AC system axis compatibility
        x_form = ACPy.ac_transformations.pln_2_pln_world_transform(i_beam)

        try:
            bbox_b, holes_b, cuts_b, __debugger__ = ACPy.ac_jointdetector.distinguish_holes_cuts(i_beam, ACIM, beam_name)
            debug_holes = holes_b
            debug_cuts = cuts_b
            debug_bbox = bbox_b
        except ValueError as e:
            print(e)
            break
        
        print("Joint detector found:\n" \
            + "\t --holes: " +  str(len(holes_b)) + "\n" \
            + "\t --cuts: " + str(len(cuts_b)) + "\n")

        # loading holes and cuts into .acim to export
        if holes_b.__len__() != 0:
            for hole_b in holes_b:
                hole_objects = ACPy.ac_hole.parse_data_from_brep(ACIM, str(beam_name), hole_b, bbox_b)
                if hole_objects is not None:
                    debug_holes = debug_holes + hole_objects
        if cuts_b.__len__() != 0:
            cut_counter = 1
            for cut_b in cuts_b:
                cut_objects = ACPy.ac_cut.parse_data_from_brep(ACIM, str(beam_name), cut_b, bbox_b)
                if cut_objects is not None:
                    debug_cuts = debug_cuts + cut_objects

        ACIM.dump_data(is_overwrite=True)
        
    # transform back for visualization
    if i_transform_back:
        x_form_back = ACPy.ac_transformations.get_inverse_transform(x_form)
        _ = [h.Transform(x_form_back) for h in debug_holes]
        _ = [c.Transform(x_form_back) for c in debug_cuts]
        _ = [d.Transform(x_form_back) for d in __debugger__]
        _ = debug_bbox.Transform(x_form_back)

    


    o_holes = debug_holes
    o_cuts = debug_cuts
    o_AABB = debug_bbox
    o__debugger__ = __debugger__





