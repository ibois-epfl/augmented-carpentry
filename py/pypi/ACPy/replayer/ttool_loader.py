import os
import json
import subprocess
import zipfile
from glob import glob

import xml.etree.ElementTree as ET

import Rhino
import ghpythonlib


def unzip_file(zip_file_path, dest_folder):
    """Unzip a file to a destination folder."""
    with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
        zip_ref.extractall(dest_folder)

    return True


def download_file(url, dest_path):
    """Download a file to a destination path."""
    curl_command = ["curl", "-o", dest_path, url]
    result = subprocess.run(curl_command)

    if result.returncode != 0:
        Rhino.RhinoApp.WriteLine(f"Error downloading {url} to {dest_path}")
        return False
    else:
        return True


def download_and_unzip_zenodo_file(url, dest_folder, filename):
    """Download an individual zip file in a zenodo dataset and unzip."""
    if not os.path.exists(dest_folder):
        os.makedirs(dest_folder)
    
    dest_path = os.path.join(dest_folder, filename)

    if not download_file(url, dest_path):
        return False
    
    if not unzip_file(dest_path, dest_folder):
        return False   

    return True


def download_ttool_model(ttool_zenodo_version, download_root_path):
    """Download all the TTool models of a specific version from Zenodo."""

    # Rhino.RhinoApp.WriteLine("Downloading TTool models...")

    metadata_url = "https://zenodo.org/api/records/" + ttool_zenodo_version
    curl_command = ["curl", metadata_url]
    metadata_raw_str = (subprocess.run(curl_command, stdout=subprocess.PIPE, text=True)).stdout

    metadata = json.loads(metadata_raw_str)
    for file in metadata["files"]:
        filename = file["key"]
        url = file["links"]["self"]

        download_and_unzip_zenodo_file(url, download_root_path, filename)


def _parse_position(positionString):
    """
    As the acit stores the position according to a Y-up coordinate system,
    we need to convert it to a Z-up system by swapping the Y and Z values.
    """

    positionString = positionString.strip()
    x, z, y = tuple(map(float, positionString.split(" ")))
    return Rhino.Geometry.Point3d(x, y, z)


def parse_acit(acit_path, scale):
    """Parse the ACIT file and return the data in a dictionary."""
    tree = ET.parse(acit_path)
    acit = tree.getroot()

    toolhead = acit.find("toolhead")
    tool_type = toolhead.attrib["type"].strip()
    if tool_type == "circularsaw":
        center = _parse_position(toolhead.find("center").text) * scale
        normal_start = _parse_position(toolhead.find("normalstart").text) * scale
        normal_end = _parse_position(toolhead.find("normalend").text) * scale
        radius = float(toolhead.find("radius").text) * scale
        blade_thickness = float(toolhead.find("bladeThickness").text) * scale
        blade_overhang = float(toolhead.find("bladeOverhang").text) * scale

        normal = normal_end - normal_start
        normal.Unitize()

        data = {
            "type": "circularsaw",
            "center": center,
            "normal": normal,
            "radius": radius,
            "blade_thickness": blade_thickness,
            "blade_overhang": blade_overhang
        }

        return data

    elif tool_type == "drillbit":
        tool_base = _parse_position(toolhead.find("toolbase").text) * scale
        tip = _parse_position(toolhead.find("tooltip").text) * scale
        eat_tip = _parse_position(toolhead.find("eattip").text) * scale
        chuck_tip = _parse_position(toolhead.find("chucktip").text) * scale
        radius = float(toolhead.find("radius").text) * scale
        
        normal = chuck_tip - eat_tip
        length = normal.Length
        normal.Unitize()

        data = {
            "type": "drillbit",
            "tool_base": tool_base,
            "tip": tip,
            "eat_tip": eat_tip,
            "chuck_tip": chuck_tip,
            "radius": radius,
            "normal": normal,
            "length": length
        }

        return data
    
    elif tool_type == "chainsaw":
        chain_base = _parse_position(toolhead.find("chainbase").text) * scale
        chain_mid = _parse_position(toolhead.find("chainmid").text) * scale
        chain_end = _parse_position(toolhead.find("chainend").text) * scale
        normal_start = _parse_position(toolhead.find("normalstart").text) * scale
        normal_end = _parse_position(toolhead.find("normalend").text) * scale
        width = float(toolhead.find("width").text) * scale
        blade_thickness = float(toolhead.find("bladeThickness").text) * scale
        blade_overhang = float(toolhead.find("bladeOverhang").text) * scale

        normal = normal_end - normal_start
        normal.Unitize()

        data = {
            "type": "chainsaw",
            "chain_base": chain_base,
            "chain_mid": chain_mid,
            "chain_end": chain_end,
            "normal": normal,
            "width": width,
            "blade_thickness": blade_thickness,
            "blade_overhang": blade_overhang
        }

        return data

    elif tool_type == "sabersaw":
        pass

    else:
        raise ValueError(f"Unknown toolhead type {toolhead.attrib['type']}")


def construct_drillbit_primitive_model(acit_data):
    """Construct a primitive model of the drillbit from the ACIT file."""
    
    base_plane = Rhino.Geometry.Plane(acit_data["eat_tip"], acit_data["normal"])
    base_circle = Rhino.Geometry.Circle(base_plane, acit_data["radius"]/2)
    primitive_cylinder = Rhino.Geometry.Cylinder(base_circle, acit_data["length"])
    brep = primitive_cylinder.ToBrep(True, True)

    return brep


def construct_circularsaw_primitive_model(acit_data):
    """Construct a primitive model of the circularsaw from the ACIT file."""
    
    # the normal will facing the outside of the blade (facing the camera), thus * -1
    base_plane = Rhino.Geometry.Plane(acit_data["center"], -acit_data["normal"])
    base_circle = Rhino.Geometry.Circle(base_plane, acit_data["radius"])
    primitive_cylinder = Rhino.Geometry.Cylinder(base_circle, acit_data["blade_thickness"])
    brep = primitive_cylinder.ToBrep(True, True)

    return brep


def construct_chainsaw_primitive_model(acit_data):
    """Construct a primitive model of the chainsaw from the ACIT file."""
    # The primitive model for chainsaw can just take the normal rebuilt model
    return None


def construct_primitive_model(acit_data):
    """Construct a primitive model from the ACIT file."""
    
    if acit_data["type"] == "drillbit":
        return construct_drillbit_primitive_model(acit_data)
    elif acit_data["type"] == "circularsaw":
        return construct_circularsaw_primitive_model(acit_data)
    elif acit_data["type"] == "chainsaw":
        return construct_chainsaw_primitive_model(acit_data)
    else:
        raise ValueError("Unknown toolhead type")


def rebuild_saw_blade_model(raw_mesh_model, acit_data):
    """Rebuild the model to give it thickness."""
    normal = acit_data["normal"]
    normal.Unitize()
    # the normal will facing the outside of the blade (facing the camera), thus * -1
    extrude_vec = -normal * acit_data["blade_thickness"]
    
    naked_edges = raw_mesh_model.GetNakedEdges()
    sorted_edges = sorted(naked_edges, key=lambda e: e.Length, reverse=True)

    # the longest edge is the blade edge
    boundary = sorted_edges[0]
    blade_face_1 = ghpythonlib.components.FragmentPatch(boundary)
    blade_face_2 = blade_face_1.Duplicate()
    blade_face_2.Translate(extrude_vec)
    extrusion = Rhino.Geometry.Extrusion.CreateExtrusion(boundary.ToNurbsCurve(), extrude_vec).ToBrep()

    model = Rhino.Geometry.Brep.JoinBreps(
        [blade_face_1, blade_face_2, extrusion],
        Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance,
        Rhino.RhinoDoc.ActiveDoc.ModelAngleToleranceRadians,
    )[0]
    
    return model


def load(ttool_model_root_path, ttool_zenodo_version_url, scale=50):
    """
    Load the TTool models of a specific version from the given root path.
    Returns a dictionary of 
    {
        model_names: {
            "model": Rhino.Geometry.Brep (the detailed model),
            "primitive": Rhino.Geometry.Brep (the representative cylinder model)
        },
        ...
    }.
    """

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
        
        if "saber" in path:
            # TODO: skip those that are not in used at the moment
            continue

        model_name = os.path.basename(path)
        ttool_models[model_name] = {}

        # create a primitive model
        acit_path = os.path.join(path, "metadata.acit")
        acit_data = parse_acit(acit_path, scale)
        primitive_model = construct_primitive_model(acit_data)

        # load the model
        model_path = os.path.join(path, "model.obj")

        raw_model = ghpythonlib.components.Import3DM(model_path, "*", "*")
        if raw_model is None:
            Rhino.RhinoApp.WriteLine(f"Error loading {model_path}")
            raise ValueError(f"Error loading .obj file. If the file exists, try re-open Rhino.")

        raw_model.Scale(scale)
        saw_blade_type_to_rebuild = ["circularsaw", "chainsaw"]
        if acit_data["type"] in saw_blade_type_to_rebuild:
            fine_model = rebuild_saw_blade_model(raw_model, acit_data)
        else:
            fine_model = Rhino.Geometry.Brep.CreateFromMesh(raw_model, True)
        
        # export the data
        ttool_models[model_name]["type"] = acit_data["type"]
        ttool_models[model_name]["raw_model"] = raw_model
        ttool_models[model_name]["model"] = fine_model
        ttool_models[model_name]["primitive_model"] = primitive_model

    return ttool_models


if __name__ == "__main__":
    ttool_model_root_path = "C:\\Users\\localuser\\Documents\\hong-bin\\replayer\\ttool_dataset_new"
    ttool_zenodo_version_url = "https://zenodo.org/record/12578820"
    ttool_models = load(ttool_model_root_path, ttool_zenodo_version_url)
    
    # a = ttool_models["circular_saw_blade_mafel_237"]