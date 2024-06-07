"""Grasshopper Script Instance"""
import System
import Rhino
import Grasshopper as gh
from Grasshopper.Kernel import GH_RuntimeMessageLevel as RML
from ghpythonlib.componentbase import executingcomponent as component

import os
import Rhino
from glob import glob

import ghpythonlib

class ACPyReplayerTToolLoader(component):
    def __init__(self):
        super(ACPyReplayerTToolLoader, self).__init__()
        self._var_output = []

    def RunScript(self, i_ttool_model_root_path: str):
        
        ttool_model_paths = glob(os.path.join(i_ttool_model_root_path, "*"))

        ttool_models = {}
        for path in ttool_model_paths:
            if path.endswith(".zip"):
                continue

            model_path = os.path.join(path, "model.obj")
            model_name = os.path.basename(path)

            model_obj = ghpythonlib.components.Import3DM(model_path, "*", "*")

            ttool_models[model_name] = model_obj
        
        return [ttool_models]
