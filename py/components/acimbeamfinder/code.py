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
import ACPy.ac_util


TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIVE_DOC = Rhino.RhinoDoc.ActiveDoc


class ACPyBeamFinder(component):
    def __init__(self):
        super(ACPyBeamFinder, self).__init__()
        self._var_output = []

    def RunScript(self,
        i_beam_name : str = "",
    ):
        ghenv.Component.Message = f"ACPyApp v{ACPy.__version__}"

        # retrieve the beams
        found_breps = ACPy.ac_util.find_beam_by_name(i_beam_name)
        ghdoc = ACTIVE_DOC

        # scale the beams for visualization
        for brep in found_breps:
            centroid = brep.GetBoundingBox(True).Center
            scale = rg.Transform.Scale(centroid, 1.1)
            brep.Transform(scale)

        o_found = found_breps

        return o_found

############################################################################################
## only for DEBUG: erase before componentize
############################################################################################
if __name__ == "__main__":
    
    comp = ACPyBeamFinder()
    o_found = comp.RunScript(
        i_beam_name
    )
