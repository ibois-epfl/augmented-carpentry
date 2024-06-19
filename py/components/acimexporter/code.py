#! python3

import sys
import os
import time
import io

import System

import Grasshopper
import Grasshopper as gh
from Grasshopper.Kernel import GH_RuntimeMessageLevel as RML
from ghpythonlib.componentbase import executingcomponent as component

import Rhino
import Rhino.Geometry as rg

import typing

import ACPy
import ACPy.ac_acim
import ACPy.ac_transformations
import ACPy.ac_jointdetector
import ACPy.ac_util
import ACPy.ac_hole
import ACPy.ac_cut

TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIVE_DOC = Rhino.RhinoDoc.ActiveDoc


class ACPyAcimExporter(component):
    def __init__(self):
        super(ACPyAcimExporter, self).__init__()
        self._var_output = []

    def RunScript(self,
        i_acim_path : str,
        i_transform_back : bool,
        i_inflate_AABB : bool,
        i_divide_tolerance : bool,
        i_dump_data : bool,
        i_beams : typing.List[rg.Brep],
        i_GUIDs : typing.List[System.Guid]
    ):
        ghenv.Component.Message = f"ACPyApp v{ACPy.__version__}"

        o_debug_holes = []
        o_debug_cuts = []
        o__debugger_o__ = []
        o_debug_bbox = []
        for idx, i_beam in enumerate(i_beams):
            debug_holes = []
            debug_cuts = []
            __debugger_o__ = []
            debug_bbox = []

            # retrieve the name of the beam from document
            beam_name = ACPy.ac_util.get_brep_object_name(i_beam, i_GUIDs[idx])
            ACIM = ACPy.ac_acim.ACIM(out_dir=i_acim_path, 
                                    out_name=beam_name)
            ACIM.add_timber(beam_name)

            # bring the beam to the XY axis for AC system axis compatibility
            x_form = ACPy.ac_transformations.pln_2_pln_world_transform(i_beam)
            
            try:
                bbox_b, holes_b, cuts_b, __debugger__ = ACPy.ac_jointdetector.distinguish_holes_cuts(
                    i_beam,
                    ACIM,
                    beam_name,
                    i_divide_tolerance,
                    i_inflate_AABB)
                _ = [debug_holes.append(h) for h in holes_b]
                _ = [debug_cuts.append(c) for c in cuts_b]
                _ = [__debugger_o__.append(d) for d in __debugger__]
                debug_bbox.append(bbox_b)
            except ValueError as e:
                print(e)
                ghenv.Component.AddRuntimeMessage(RML.Error, str(e))
                ACPy.ac_util.highlight_object_by_GUID(i_GUIDs[idx])
                break
            
            print("Joint detector found:\n" \
                + "\t --holes: " +  str(len(holes_b)) + "\n" \
                + "\t --cuts: " + str(len(cuts_b)) + "\n")

            # loading holes and cuts into .acim to exports
            if holes_b.__len__() != 0:
                for hole_b in holes_b:
                    hole_objects = ACPy.ac_hole.parse_data_from_brep(ACIM, str(beam_name), hole_b, bbox_b)
                    if hole_objects is not None:
                        _ = [debug_holes.append(h) for h in hole_objects]
            if cuts_b.__len__() != 0:
                cut_counter = 1
                for cut_b in cuts_b:
                    cut_objects = ACPy.ac_cut.parse_data_from_brep(ACIM, str(beam_name), cut_b, bbox_b)
                    if cut_objects is not None:
                        _ = [debug_cuts.append(c) for c in cut_objects]

            if i_dump_data:
                ACIM.dump_data(is_overwrite=True)
            
            # transform back for visualization
            if i_transform_back:
                x_form_back = ACPy.ac_transformations.get_inverse_transform(x_form)
                _ = [h.Transform(x_form_back) for h in debug_holes]
                _ = [c.Transform(x_form_back) for c in debug_cuts]
                _ = [d.Transform(x_form_back) for d in __debugger_o__]
                _ = [b.Transform(x_form_back) for b in debug_bbox]

            _ = [o_debug_holes.append(h) for h in debug_holes]
            _ = [o_debug_cuts.append(c) for c in debug_cuts]
            _ = [o__debugger_o__.append(d) for d in __debugger_o__]
            _ = [o_debug_bbox.append(b) for b in debug_bbox]

        o_holes = o_debug_holes
        o_cuts = o_debug_cuts
        # o_AABB = o_debug_bbox
        # o__debugger__ = o__debugger_o__

        return o_holes, o_cuts


############################################################################################
## only for DEBUG: erase before componentize
############################################################################################
if __name__ == "__main__":
    comp = ACPyAcimExporter()
    o_holes, o_cuts = comp.RunScript(
        i_acim_path,
        i_transform_back,
        i_inflate_AABB,
        i_divide_tolerance,
        i_dump_data,
        i_beams,
        i_GUIDs
    )