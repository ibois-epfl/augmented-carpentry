import os
import subprocess
from glob import glob

import Rhino
import ghpythonlib


def download_and_unzip_zenodo_dataset(url, dest_folder, filename):
    if not os.path.exists(dest_folder):
        os.makedirs(dest_folder)
    
    dest_path = os.path.join(dest_folder, filename)

    curl_command = ["curl", "-o", dest_path, url]

    result = subprocess.run(curl_command)
    
    if result.returncode != 0:
        Rhino.RhinoApp.WriteLine(f"Error downloading {filename} from {url}, please check the file manually.")
        return False
    else:
        # unzip the file
        unzip_command = ["unzip", dest_path, "-d", dest_folder]
        result = subprocess.run(unzip_command)
        if result.returncode != 0:
            print(f"Error unzipping {filename}")
            return False

    return True


def download_ttool_model(ttool_zenodo_version, download_root_path):
    import json

    Rhino.RhinoApp.WriteLine("Downloading TTool models...")

    metadata_url = "https://zenodo.org/api/records/" + ttool_zenodo_version
    curl_command = ["curl", metadata_url]
    metadata_raw_str = (subprocess.run(curl_command, stdout=subprocess.PIPE, text=True)).stdout

    metadata = json.loads(metadata_raw_str)
    for file in metadata["files"]:
        filename = file["key"]
        url = file["links"]["self"]

        download_and_unzip_zenodo_dataset(url, download_root_path, filename)


def load(ttool_model_root_path, ttool_zenodo_version_url):
    zenodo_version = ttool_zenodo_version_url.split("/")[-1]
    
    ttool_model_version_path = os.path.join(ttool_model_root_path, zenodo_version)

    if not os.path.exists(ttool_model_version_path):
        os.makedirs(ttool_model_version_path)
        download_ttool_model(zenodo_version, ttool_model_version_path)

    # load all the mesh files
    ttool_model_paths = glob(os.path.join(ttool_model_version_path, "*"))

    ttool_models = {}
    for path in ttool_model_paths:
        if path.endswith(".zip"):
            continue

        model_path = os.path.join(path, "model.obj")
        model_name = os.path.basename(path)

        model_obj = ghpythonlib.components.Import3DM(model_path, "*", "*")
        model_obj.Scale(50)

        ttool_models[model_name] = model_obj

    return ttool_models