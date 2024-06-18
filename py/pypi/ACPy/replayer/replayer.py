import log_loader
import acim_loader
import ttool_mesh_loader
import camera_model

class Replayer:
    def __init__(self):
        self.log_data = None

    def load(self, log_root_path: str, exp_id: str, ttool_download_path: str):
        self.log_data = log_loader.load(log_root_path, exp_id)
        
        # load ACIM model
        self.acim_data = acim_loader.load(self.log_data.acim_model_path)

        # load tool mesh
        self.ttool_models = ttool_mesh_loader.load(ttool_download_path, self.log_data.ttool_zenodo_version_url)

        # camera model
        self.camera_model = camera_model.get_brep()


if __name__ == "__main__":
    replayer = Replayer()
    replayer.load(log_root_path, exp_id, ttool_download_path)

    bbox = replayer.acim_data.bbox
    all_cuts = [x[1] for x in replayer.acim_data.cuts.items()]
    all_holes = [x[1] for x in replayer.acim_data.holes.items()]

    camera = replayer.camera_model