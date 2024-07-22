"""Grasshopper Script Instance"""
import subprocess

import os
import Rhino

## FOR DEBUG
# import sys
# sys.path.append("/Users/petingo/p/augmented-carpentry/py/pypi")

from ACPy.replayer.capture_img import capture_img

class ACPyReplayerCaptureImg(component):
    def __init__(self):
        super(ACPyReplayerCaptureImg, self).__init__()

    def RunScript(self,
            i_frame_idx,
            i_frame_count,
            i_frame_rate,
            i_output_path,
            i_ffmpeg_path):
        
        # create folder if not exists
        if not os.path.exists(i_output_path):
            os.makedirs(i_output_path)

        img_output_path = os.path.join(i_output_path, f"frame_{i_frame_idx:06}.png")
        capture_img(img_output_path)

        if i_frame_idx == i_frame_count - 1:
            glob_pattern = os.path.join(i_output_path, "frame_*.png")
            video_output_path = os.path.join(i_output_path, "output.mp4")

            if i_ffmpeg_path is None or len(i_ffmpeg_path) == 0:
                i_ffmpeg_path = "ffmpeg"
            ffmpeg_command = [i_ffmpeg_path, "-y", "-framerate", str(i_frame_rate), "-pattern_type",  "glob", "-i", glob_pattern, "-c:v", "libx264", "-pix_fmt", "yuv420p", video_output_path]
            
            result = subprocess.run(ffmpeg_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            if result.returncode != 0:
                Rhino.RhinoApp.WriteLine(f"FFmpeg encounter error while generating video.")
                Rhino.RhinoApp.WriteLine(" ".join(ffmpeg_command))
                Rhino.RhinoApp.WriteLine(result.stdout.decode('utf-8'))
                Rhino.RhinoApp.WriteLine(result.stderr.decode('utf-8'))
                return False
            else:
                return True

# if __name__ == "__main__":
#     ACPyReplayerCaptureImg.RunScript(frame_idx, frame_count, frame_rate, output_path)