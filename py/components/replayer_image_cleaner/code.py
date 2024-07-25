"""Grasshopper Script Instance"""
import subprocess
import os
from glob import glob

import Rhino

## FOR DEBUG
# import sys
# sys.path.append("/Users/petingo/p/augmented-carpentry/py/pypi")

from ACPy.replayer.capture_img import capture_img

class ACPyReplayerCaptureImg(component):
    def __init__(self):
        super(ACPyReplayerCaptureImg, self).__init__()

    def RunScript(self,
            i_path,
            i_run):
        
        if i_run:
                glob_pattern = os.path.join(i_path, "frame_*.png")
                img_files = glob(glob_pattern)
                for f in img_files:
                    os.remove(f)

# if __name__ == "__main__":
#     ACPyReplayerCaptureImg.RunScript(frame_idx, frame_count, frame_rate, output_path)