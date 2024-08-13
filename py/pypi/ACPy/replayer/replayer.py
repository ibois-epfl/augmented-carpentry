# ## FOR DEBUG
import sys
sys.path.append("/Users/petingo/p/augmented-carpentry/py/pypi/ACPy/replayer")

from . import log_loader
from . import acim_loader
from . import ttool_loader
from . import camera_model

import Rhino

class Replayer:
    def __init__(self):
        self.log_data = None

    def load(self, log_root_path: str, exp_id: str, ttool_download_path: str):
        self.log_data = log_loader.load(log_root_path, exp_id)
        
        # load ACIM model
        self.acim_data = acim_loader.load(self.log_data.acim_model_path)

        # load tool mesh
        self.ttool_models = ttool_loader.load(ttool_download_path, self.log_data.ttool_zenodo_version_url)

        # camera model
        self.camera_model = camera_model.get_brep()

    def set_camera_model(self, camera_model):
        self.camera_model = camera_model

    def generate_scene_at_frame(self, frame_index: int):
        """
        Export the 3D model with the transformation at the given frame index.
        """
        if frame_index < 0 or frame_index >= self.log_data.frame_count:
            raise ValueError("The frame index is out of range.")
        
        # get the data at the given frame index
        acim_transform = self._transform_matrix_to_gh_transform(self.log_data.all_event_data["ACIM-transform"].get(frame_index))
        slam_transform = self._transform_matrix_to_gh_transform(self.log_data.all_event_data["SLAM"].get(frame_index))
        
        ttool_head = self.log_data.all_event_data["TTool-head"].get(frame_index)
        ttool_status, ttool_transformation = self.log_data.all_event_data["TTool-pose"].get(frame_index)
        ttool_transformation = self._transform_matrix_to_gh_transform(ttool_transformation)

        acim_activate_component = self.log_data.all_event_data["ACIM-activate-component"].get(frame_index)
        acim_component_status = self.log_data.all_event_data["ACIM-component-status"].get(frame_index)

        # copy the 3d models and transform them
        camera_model = self.camera_model.Duplicate()
        camera_model.Transform(slam_transform)

        tool_model = self.ttool_models[ttool_head]["model"].Duplicate()
        tool_model.Transform(ttool_transformation)

        ttool_primitive_model = self.ttool_models[ttool_head]["primitive_model"].Duplicate()
        ttool_primitive_model.Transform(ttool_transformation)

        acim_bbox = self.acim_data.bbox.Duplicate()
        acim_bbox.Transform(acim_transform)
        
        acim_activated_component = []
        acim_done_component = []
        acim_not_done_component = []

        all_components = list(self.acim_data.cuts.items()) + list(self.acim_data.holes.items())
        for name, brep in all_components:
            brep = brep.Duplicate()
            brep.Transform(acim_transform)

            if name == acim_activate_component:
                acim_activated_component.append(brep)
            
            elif acim_component_status[name] == "Done":
                acim_done_component.append(brep)
            
            else:
                acim_not_done_component.append(brep)

        # save the model to the scene
        scene = {}
        scene["camera_model"] = camera_model
        scene["tool_model"] = tool_model
        scene["tool_primitive_model"] = ttool_primitive_model
        scene["acim_bbox"] = acim_bbox
        scene["acim_activated_component"] = acim_activated_component
        scene["acim_done_component"] = acim_done_component
        scene["acim_not_done_component"] = acim_not_done_component

        return scene
    

    def _transform_matrix_to_gh_transform(self, matrix):
        """
        Convert a 4x4 matrix to a Grasshopper Transform object.
        """

        transformation = Rhino.Geometry.Transform()
        transformation.M00 = matrix[0][0]
        transformation.M01 = matrix[0][1]
        transformation.M02 = matrix[0][2]
        transformation.M03 = matrix[0][3]
        transformation.M10 = matrix[1][0]
        transformation.M11 = matrix[1][1]
        transformation.M12 = matrix[1][2]
        transformation.M13 = matrix[1][3]
        transformation.M20 = matrix[2][0]
        transformation.M21 = matrix[2][1]
        transformation.M22 = matrix[2][2]
        transformation.M23 = matrix[2][3]
        transformation.M30 = matrix[3][0]
        transformation.M31 = matrix[3][1]
        transformation.M32 = matrix[3][2]
        transformation.M33 = matrix[3][3]

        return transformation
    

# if __name__ == "__main__":
#     replayer = Replayer()
#     replayer.load(log_root_path, exp_id, ttool_download_path)

#     camera = replayer.camera_model
#     bbox = replayer.acim_data.bbox
#     all_cuts = [x[1] for x in replayer.acim_data.cuts.items()]
#     all_holes = [x[1] for x in replayer.acim_data.holes.items()]

#     frame_count = replayer.log_data.frame_count

#     scene = replayer.generate_scene_at_frame(100)
#     tool_mesh = scene["tool_mesh"]
#     camera_model = scene["camera_model"]
#     acim_breps = [scene["acim_bbox"]] + scene["acim_activated_component"] + scene["acim_done_component"] + scene["acim_not_done_component"]
