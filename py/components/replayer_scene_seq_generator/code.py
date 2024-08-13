import ACPy
from ACPy.replayer.gh_loop import GHLoop

class ACPyReplayerSceneSeqGenerator(component):
    def __init__(self):
        super(ACPyReplayerSceneSeqGenerator, self).__init__()

    def RunScript(self,
            i_replayer,
            i_frame_start: int,
            i_frame_end: int,
            i_run: bool,
            i_reset: bool):
        
        if i_reset:
            loop.reset()
            
        if not i_run:
            return None, None, None, None, None, None, None, None, None

        loop = GHLoop(range(i_frame_start, i_frame_end), ghenv)
    
        frame_idx, frame_absolute_idx = loop.get_next()
        frame_count = len(loop)
        
        scene = i_replayer.generate_scene_at_frame(frame_absolute_idx)

        # object to return
        frame_idx = frame_idx
        frame_count = frame_count
        camera_model = scene["camera_model"]
        tool_model = scene["tool_model"]
        tool_primitive_model = scene["tool_primitive_model"]
        acim_bbox = scene["acim_bbox"]
        acim_activated_component = scene["acim_activated_component"]
        acim_done_component = scene["acim_done_component"]
        acim_not_done_component = scene["acim_not_done_component"]

        return frame_idx, frame_count, camera_model, tool_model, tool_primitive_model, acim_bbox, acim_activated_component, acim_done_component, acim_not_done_component