import os
from glob import glob

import Rhino
import ghpythonlib

def load(download_root_path, ttool_zenodo_version_url):
    print(ttool_zenodo_version_url)
    zenodo_version = ttool_zenodo_version_url.split("/")[-1]
    
    # TODO: check if the model is already exist and download only if it is not exist
    ttool_model_root_path = os.path.join(download_root_path, zenodo_version)

    print(ttool_model_root_path)

    # load all the mesh files
    ttool_model_paths = glob(os.path.join(ttool_model_root_path, "*"))

    ttool_models = {}
    for path in ttool_model_paths:
        if path.endswith(".zip"):
            continue

        model_path = os.path.join(path, "model.obj")
        model_name = os.path.basename(path)

        print(model_path)

        model_obj = ghpythonlib.components.Import3DM(model_path, "*", "*")
        model_obj.Scale(50)

        ttool_models[model_name] = model_obj

    return ttool_models