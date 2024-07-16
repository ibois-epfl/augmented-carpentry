"""Grasshopper Script Instance"""
import System
import Rhino

import os
import Rhino
import ghpythonlib

class ACPyReplayerSceneGenerator(component):
    def __init__(self):
        super(ACPyReplayerSceneGenerator, self).__init__()

    def RunScript(self, i_replayer, i_frame_id: int):
        scene = i_replayer.generate_scene_at_frame(i_frame_id)

        camera_model = scene["camera_model"]
        tool_mesh = scene["tool_mesh"]
        acim_bbox = scene["acim_bbox"]
        acim_activated_component = scene["acim_activated_component"]
        acim_done_component = scene["acim_done_component"]
        acim_not_done_component = scene["acim_not_done_component"]

        return camera_model, tool_mesh, acim_bbox, acim_activated_component, acim_done_component, acim_not_done_component

# if __name__ == "__main__":
#     camera_model, tool_mesh, acim_bbox, acim_activated_component, acim_done_component, acim_not_done_component = \
#         ACPyReplayerSceneGenerator().RunScript(i_replayer, i_frame_id)