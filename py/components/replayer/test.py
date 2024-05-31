# r: numpy

import numpy as np

pose_log = {
    "SLAM": {},
    "ACIM-transform": {},
    "TTool-pose": {}
}

pose_log_index = {
    "SLAM": [],
    "ACIM-transform": [],
    "TTool-pose": []
}

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

def get_last_traced_frame_id(log_index, target_frame):
    """
    Get the last frame id that is smaller than target_frame
    """
    for i in log_index:
        if i > target_frame:
            break
    return i

current_frame = 0
with open(i_log_file) as f:
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
            current_frame = int(line.split(' ')[0][1:])
            continue
        
        # others
        arr = line.split(' ')
        if arr[0] == "SLAM":
            pose_log["SLAM"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[1:])))
            pose_log_index["SLAM"].append(current_frame)
        elif arr[0] == "ACIM-transform":
            pose_log["ACIM-transform"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[1:])))
            pose_log_index["ACIM-transform"].append(current_frame)
        elif arr[0] == "TTool-pose":
            pose_log["TTool-pose"][current_frame] = convert_log_pose_to_transform_matrix(list(map(float, arr[2:])))
            pose_log_index["TTool-pose"].append(current_frame)


print(pose_log_index)


# determine the last frame with pose smaller than i_target_frame
slam_pose = pose_log["SLAM"][get_last_traced_frame_id(pose_log_index["SLAM"], i_target_frame)]
acim_pose = pose_log["ACIM-transform"][get_last_traced_frame_id(pose_log_index["ACIM-transform"], i_target_frame)]
ttool_pose = pose_log["TTool-pose"][get_last_traced_frame_id(pose_log_index["TTool-pose"], i_target_frame)]

print(slam_pose)
print(acim_pose)
print(ttool_pose)

o_slam_pose = slam_pose.flatten().tolist()
o_acim_pose = acim_pose.flatten().tolist()
o_ttool_pose = ttool_pose.flatten().tolist()