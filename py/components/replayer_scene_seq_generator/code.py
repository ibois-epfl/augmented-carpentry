"""Grasshopper Script Instance"""
import System
import Rhino

import os
import Rhino
import ghpythonlib
import scriptcontext as sc

IS_WIP = "ACPY_REPLAYER_IS_WIP"
CURR_IDX = "ACPY_REPLAYER_CURR_IDX"
FRAME_CNT = "ACPY_REPLAYER_FRAME_CNT"

class ACPyReplayerSceneSeqGenerator(component):
    def __init__(self):
        super(ACPyReplayerSceneSeqGenerator, self).__init__()

    def RunScript(self, i_replayer, i_frame_id, i_reset):
        frame_start = 64400
        frame_end = 64500

        empty_return_value = (-1, -1, None, None, None, None, None, None, None)

        if i_reset:
            if sc.sticky.has_key(IS_WIP):
                sc.sticky.pop(IS_WIP)
            return empty_return_value

        # init 
        if not sc.sticky.has_key(IS_WIP):
            sc.sticky[IS_WIP] = True
            sc.sticky[CURR_IDX] = frame_start
            sc.sticky[FRAME_CNT] = 0

        # main loop
        if sc.sticky[CURR_IDX] > frame_end:
            return empty_return_value
        
        scene = i_replayer.generate_scene_at_frame(sc.sticky[CURR_IDX])
        print(sc.sticky[CURR_IDX])

        # object to return
        frame_id = sc.sticky[CURR_IDX]
        frame_count = sc.sticky[FRAME_CNT]
        camera_model = scene["camera_model"]
        tool_model = scene["tool_model"]
        tool_primitive_model = scene["tool_primitive_model"]
        acim_bbox = scene["acim_bbox"]
        acim_activated_component = scene["acim_activated_component"]
        acim_done_component = scene["acim_done_component"]
        acim_not_done_component = scene["acim_not_done_component"]

        sc.sticky[CURR_IDX] += 1
        sc.sticky[FRAME_CNT] += 1

        return frame_id, frame_count, camera_model, tool_model, tool_primitive_model, acim_bbox, acim_activated_component, acim_done_component, acim_not_done_component

if __name__ == "__main__":

    frame_id, frame_count, camera_model, tool_model, tool_primitive_model, acim_bbox, acim_activated_component, acim_done_component, acim_not_done_component = \
                ACPyReplayerSceneSeqGenerator().RunScript(i_replayer, None, i_reset)