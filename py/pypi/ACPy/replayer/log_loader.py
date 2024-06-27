import Rhino

import os
import zipfile
from glob import glob

import numpy as np

from log_data import LogEventData, LogData

def load(root_path: str, exp_id: str):
    """
    Load the log data from the given root path and experiment ID.
    
    Returns:
        all_event_data: LogData
    """

    log_events = [
        "SLAM",
        "TTool-head",
        "TTool-pose",
        "ACIM-activate-component",
        "ACIM-component-status",
        "ACIM-transform"
    ]

    all_event_data = {}
    for e in log_events:
        all_event_data[e] = LogEventData()

    exp_folders = _get_exp_folder_paths(root_path, exp_id)

    component_status = {}
    
    # start parsing the log files
    current_frame = 0
    for i, path in enumerate(exp_folders):
        log_filepath = os.path.join(path, "log.txt")

        if i == 0:
            acim_model_path = os.path.join(path, "AC_info_model.acim")
            scanned_model_path = os.path.join(path, "scanned_model.ply")

        with open(log_filepath) as f:
            start_flag = False

            for line in f:
                line = line.strip()
                if len(line) == 0:
                    continue

                # parse header for the fist log file
                if i == 0 and not start_flag:
                    if line.startswith("Created Time"):
                        timestamp = line.split(":")[1].strip()
                    elif line.startswith("TTool Zenodo Version"):
                        ttool_zenodo_version_url = "".join(line.split(":")[1:]).strip()

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
                    all_event_data["ACIM-transform"].add(
                        current_frame,
                        _convert_log_pose_to_transform_matrix(list(map(float, arr[1:])))
                    )
                
                if event_type == "SLAM":
                    all_event_data["SLAM"].add(
                        current_frame,
                        np.linalg.inv(_convert_log_pose_to_transform_matrix(list(map(float, arr[1:]))))
                    )

                elif event_type == "TTool-head":
                    all_event_data["TTool-head"].add(
                        current_frame,
                        arr[1] # head name
                    )

                elif event_type == "TTool-pose":
                    all_event_data["TTool-pose"].add(
                        current_frame,
                        (arr[1], _convert_log_pose_to_transform_matrix(list(map(float, arr[2:])))) # (ttool status, pose)
                    )

                elif event_type == "ACIM-activate-component":
                    all_event_data["ACIM-activate-component"].add(
                        current_frame,
                        arr[1] # component name
                    )

                elif event_type == "ACIM-component-status":
                    component_status[arr[1]] = arr[2]

                    all_event_data["ACIM-component-status"].add(
                        current_frame,
                        component_status.copy()
                    )
        
        current_frame += 1

    log_data = LogData(all_event_data, timestamp, current_frame, acim_model_path, scanned_model_path, ttool_zenodo_version_url)

    return log_data


def _get_exp_folder_paths(root_path: str, exp_id: str):
    """
    Get the paths of the log folders belonging to the experiment ID.
    """

    if root_path is None:
        raise ValueError("The root path is None")
    
    if exp_id is None:
        raise ValueError("The experiment ID is None")

    all_paths = glob(os.path.join(root_path, "*"))

    exp_folders = []
    for path in all_paths:
        basename = os.path.basename(path)

        if basename.endswith(".zip"):
            with zipfile.ZipFile(path, 'r') as zip_ref:
                zip_ref.extractall(root_path)
            path = path[:-4]

        folder_exp_id = basename.split("_")[0]
        if folder_exp_id == exp_id:
            exp_folders.append(path)
    exp_folders.sort()

    return exp_folders


def _convert_log_pose_to_transform_matrix(log: list):
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

