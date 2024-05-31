# r: numpy

import os

import Grasshopper
import Grasshopper as gh
from Grasshopper.Kernel import GH_RuntimeMessageLevel as RML
from ghpythonlib.componentbase import executingcomponent as component

import Rhino
import Rhino.Geometry as rg
import zipfile

from glob import glob

import numpy as np

def convert_log_pose_to_transform_matrix(log: list):
    """
    Convert log pose ([t.x, t.y, t.z, q.x, q.y, q.z, q.w]) to transform matrix
    """
    t = np.array(log[:3])
    q = np.array(log[3:])
    q = q / np.linalg.norm(q)
    R = np.array([
        [1 - 2*q[1]*q[1] - 2*q[2]*q[2], 2*q[0]*q[1] - 2*q[2]*q[3], 2*q[0]*q[2] + 2*q[1]*q[3]],
        [2*q[0]*q[1] + 2*q[2]*q[3], 1 - 2*q[0]*q[0] - 2*q[2]*q[2], 2*q[1]*q[2] - 2*q[0]*q[3]],
        [2*q[0]*q[2] - 2*q[1]*q[3], 2*q[1]*q[2] + 2*q[0]*q[3], 1 - 2*q[0]*q[0] - 2*q[1]*q[1]]
    ])
    return np.vstack([np.hstack([R, t.reshape(-1, 1)]), np.array([0, 0, 0, 1])])

all_paths = glob(os.path.join(root_path, "*"))

exp_folders = []
for path in all_paths:
    basename = os.path.basename(path)

    if basename.endswith(".zip"):
        with zipfile.ZipFile(path, 'r') as zip_ref:
            zip_ref.extractall(root_path)
        path = path[:-4]

    if basename.startswith(exp_id):
        exp_folders.append(path)
exp_folders.sort()

events = [
    "SLAM",
    "TTool-head",
    "TTool-pose",
    "ACIM-activate-component",
    "ACIM-component-status",
    "ACIM-transform"
]

event_log = {}
event_log_index = {}

for e in events:
    event_log[e] = {}
    event_log_index[e] = []

current_frame = 0

for i, path in enumerate(exp_folders):
    log_filepath = os.path.join(path, "log.txt")

    with open(log_filepath) as f:
        start_flag = False

        for line in f:
            # start flag
            if "[Init]" in line:
                start_flag = True
                continue
            
            if not start_flag:
                continue
            
            # frame number
            if line[0] == '#':
                current_frame += 1
                continue
            
            # others events
            arr = line.split(' ')
            event_type = arr[0]

            # for ACIM-transform, we assume that it is initialized at the first log sequence
            if i == 0 and event_type == "ACIM-transform":
                event_log["ACIM-transform"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[1:])))
                event_log_index["ACIM-transform"].append(current_frame)

            if event_type == "SLAM":
                event_log["SLAM"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[1:])))
                event_log_index["SLAM"].append(current_frame)

            elif event_type == "TTool-head":
                event_log["TTool-head"][current_frame] = arr[1]
                event_log_index["TTool-head"].append(current_frame)
            elif event_type == "TTool-pose":
                event_log["TTool-pose"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[2:])))
                event_log_index["TTool-pose"].append(current_frame)

            elif event_type == "ACIM-activate-component":
                event_log["ACIM-activate-component"][current_frame] = arr[1]
                event_log_index["ACIM-activate-component"].append(current_frame)
            elif event_type == "ACIM-component-status":
                event_log["ACIM-component-status"][current_frame] = (arr[1], arr[2])
                event_log_index["ACIM-component-status"].append(current_frame)
    
    current_frame += 1

