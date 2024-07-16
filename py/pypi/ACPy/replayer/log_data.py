import numpy as np
import bisect

class LogEventData:
    """
    For collecting the log event data based on the frame index.
    The data type can be anything like pose (4x4 transformation matrix) or string.
    It should be constructed in chronological order.
    """
    def __init__(self):
        self.frameIDs = []
        self.dataCollection = []


    def add(self, index, data):
        """
        Add a data point at the given index.
        """
        if len(self.frameIDs) > 0 and index < self.frameIDs[-1]:
            raise ValueError("The pose data should be constructed in chronological order.")

        if len(self.frameIDs) > 0 and index == self.frameIDs[-1]:
            self.dataCollection[-1] = data
        else:
            self.frameIDs.append(index)
            self.dataCollection.append(data)
    

    def get(self, index):
        """
        Get the pose data at the given index.
        """

        targetArrIdx = bisect.bisect_right(self.frameIDs, index) - 1
        return self.dataCollection[targetArrIdx]
        
class LogData:
    def __init__(self, log_event_data, timestamp, frame_count, acim_model_path, scanned_model_path, ttool_zenodo_version_url):
        self.all_event_data = log_event_data
        self.timestamp = timestamp
        self.frame_count = frame_count
        self.acim_model_path = acim_model_path
        self.scanned_model_path = scanned_model_path
        self.ttool_zenodo_version_url = ttool_zenodo_version_url

        