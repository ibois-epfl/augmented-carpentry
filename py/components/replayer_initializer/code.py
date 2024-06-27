"""Grasshopper Script Instance"""
import System
import Rhino

import os
import Rhino
import ghpythonlib

from pypi.ACPy.replayer.replayer import Replayer

class ACPyReplayerInitializer(component):
    def __init__(self):
        super(ACPyReplayerInitializer, self).__init__()

    def RunScript(self, i_log_root_path: str, i_exp_id: str, i_ttool_download_path: str, i_camera_model):
        replayer = Replayer()
        replayer.load(i_log_root_path, i_exp_id, i_ttool_download_path)

        if i_camera_model:
            replayer.set_camera_model(i_camera_model)

        return replayer, replayer.log_data.frame_count