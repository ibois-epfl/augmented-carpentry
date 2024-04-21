#! python3
""" Tester python for the pypi module """


import Rhino
import Rhino.Geometry as rg

global TOL_DOC
TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIV_DOC = Rhino.RhinoDoc.ActiveDoc

import ACPy
import ACPy.ac_acim
import ACPy.ac_transformations
import ACPy.ac_jointdetector

import ACPy.ac_hole
import ACPy.ac_cut

if __name__ == "__main__":
    print(f"Version pacakge: {ACPy.__version__}")

    print("Hello from the pypi module!")
    print("Tolerance: ", TOL_DOC)
    print("Active Doc: ", ACTIV_DOC)
    print("Rhino.Geometry: ", rg)
    print("Rhino: ", Rhino)

    ACIM = ACPy.ac_acim.ACIM(i_acim_path)

    o_OUTs = []

    for beam in i_beams:
        # get object GUID
        p_GUID = "1234"  #FIXME: find a way to get the GUID if the object come from doc
        ACIM.add_timber(p_GUID)

        x_form = ACPy.ac_transformations.pln_2_pln_world_transform(beam)
        # x_form_back = acpy.ac_transformations.get_inverse_transform(x_form)
        # beam.Transform(x_form_back)

        bbox = beam.GetBoundingBox(True)
        bbox_b = bbox.ToBrep()
        ACIM.add_bbox(p_GUID, bbox.GetCorners())

        brep_result = rg.Brep.CreateBooleanDifference(bbox_b, beam, ACTIV_DOC.ModelAbsoluteTolerance)
        if brep_result is None or len(brep_result) == 0:
            print("No breps found after boolean difference. Exiting...")

        holes_b, cuts_b = ACPy.ac_jointdetector.distinguish_holes_cuts(brep_result)
        print("Found:\n" \
            + "\t --holes: " +  str(len(holes_b)) + "\n" \
            + "\t --cuts: " + str(len(cuts_b)) + "\n")

        ############################################################

        # analyse and loading holes and cuts into .acim
        if holes_b.__len__() != 0:
            for hole_b in holes_b:
                o_OUTs.append(hole_b)  # FIXME: this a test
                # vd.addBrep(hole_b, clr=(255, 255, 0, 30))
                # print(holes_b)
                ACPy.ac_hole.parse_data_from_brep(ACIM, str(p_GUID), hole_b, bbox_b)

        if cuts_b.__len__() != 0:
            cut_counter = 1
            for cut_b in cuts_b:
                o_OUTs.append(cut_b)
                # vd.addBrep(cut_b, clr=(255, 0, 255, 30))
                ACPy.ac_cut.parse_data_from_brep(ACIM, str(p_GUID), cut_b, bbox_b)


    # o_OUTs.append(beam)
    ACIM.dump_data(is_overwrite=True)

    o_brep = o_OUTs





