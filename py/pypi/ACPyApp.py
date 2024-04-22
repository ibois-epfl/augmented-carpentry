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

    # the export acim object
    ACIM = ACPy.ac_acim.ACIM(i_acim_path)

    o_OUTs = []  #FIXME: test
    for idx, beam in enumerate(i_beams):
        # retrieve the name of the beam from document
        beam_name = ACPy.ac_util.get_brep_object_name(beam, i_GUIDs[idx])
        ACIM.add_timber(beam_name)

        # bring the beam to the XY axis for AC system axis compatibility
        x_form = ACPy.ac_transformations.pln_2_pln_world_transform(beam)

        bbox_b, holes_b, cuts_b = ACPy.ac_jointdetector.distinguish_holes_cuts(beam, ACIM, beam_name)
        print("Found:\n" \
            + "\t --holes: " +  str(len(holes_b)) + "\n" \
            + "\t --cuts: " + str(len(cuts_b)) + "\n")

        # loading holes and cuts into .acim to export
        if holes_b.__len__() != 0:
            for hole_b in holes_b:
                o_OUTs.append(hole_b)  # FIXME: this a test
                ACPy.ac_hole.parse_data_from_brep(ACIM, str(beam_name), hole_b, bbox_b)
        if cuts_b.__len__() != 0:
            cut_counter = 1
            for cut_b in cuts_b:
                o_OUTs.append(cut_b)
                ACPy.ac_cut.parse_data_from_brep(ACIM, str(beam_name), cut_b, bbox_b)


    ACIM.dump_data(is_overwrite=True)

    # o_brep = o_OUTs





