i_ttool_models = i_ttool_models[0]
event_log = i_event_log[0]
event_log_index = i_event_log_index[0]
request_frame = i_request_frame

def get_last_traced_frame_id(log_index, request_frame_id):
    """
    Get the last frame id that is smaller than request_frame_id
    """
    for i in log_index:
        if i > request_frame_id:
            break
    return i

acim_pose = event_log["ACIM-transform"][0]

slam_pose = event_log["SLAM"][get_last_traced_frame_id(event_log_index["SLAM"], request_frame)]

ttool_head = event_log["TTool-head"][get_last_traced_frame_id(event_log_index["TTool-head"], request_frame)]
ttool_pose = event_log["TTool-pose"][get_last_traced_frame_id(event_log_index["TTool-pose"], request_frame)]

