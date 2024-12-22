#! python3
#r: pillow
#r: Wand

import System
import System.Drawing

import math
import sys
import os

from wand.image import Image
from wand.api import library

import Rhino
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs


def gaussian(x, mu, sigma):
    return (1.0 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2)

def print_progress_bar(
        iteration, total,
        prefix='', suffix='',
        decimals=1, length=10,
        fill='▒', empty='■'):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filled_length = int(length * iteration // total)
    bar = fill * filled_length + empty * (length - filled_length)
    Rhino.RhinoApp.SetCommandPrompt(f'{prefix} |{bar}| {percent}% {suffix}')
    if iteration == total:
        Rhino.RhinoApp.SetCommandPrompt(f'{prefix} |{bar}| {percent}% {suffix}\n')

def main() -> None:
    #------------------------------------------------------------
    # Rhin commandline options
    #------------------------------------------------------------
    start_log = \
    ">" * 60 + \
        r"""
                                                                 __  __       __
        >-->-->    .--------..-----..--.--..-----.  |__||  |_     |  |  >-->-->
          >-->-->  |          ||   _   ||   |   ||   -__|  |  ||   _|    |__|    >-->-->
        >-->-->    |__|__|__||_____| \___/ |_____|  |__||____|  |__|  >-->-->
        """ + "\n" + \
        "Author: @AndreaSettimi: andrea.settimi@epfl.ch (IBOIS,EPFL)" + "\n" + \
        "Description: Animate a mesh object in Rhino and save the animation as a gif." + "\n" + \
        "Usage: Select an object to animate and set the options." + "\n" + \
    ">" * 60
    print(start_log)

    go = Rhino.Input.Custom.GetObject()
    go.SetCommandPrompt("Select object to animate")
    go.AcceptNothing(True)
    go.ClearCommandOptions()
    go.EnableHighlight(False)
    __OPT_is_saving_gif = Rhino.Input.Custom.OptionToggle(False, "Off", "On")
    __OPT_transparent_background = Rhino.Input.Custom.OptionToggle(True, "Off", "On")
    __OPT_fps = Rhino.Input.Custom.OptionInteger(30, 0, 120)
    __OPT_duration = Rhino.Input.Custom.OptionInteger(3500, 1, 10000)
    _build_folder = os.path.dirname(Rhino.RhinoDoc.ActiveDoc.Path)
    __OPT_width = Rhino.Input.Custom.OptionInteger(1500, 1, 5000)
    __OPT_height = Rhino.Input.Custom.OptionInteger(1500, 1, 5000)
    go.AddOptionToggle("isSavingGif", __OPT_is_saving_gif)
    go.AddOptionToggle("TransparentBackground", __OPT_transparent_background)
    go.AddOptionInteger("Fps", __OPT_fps)
    go.AddOptionInteger("Duration_ms", __OPT_duration)
    go.AddOption("BuildDirectory")
    go.AddOptionInteger("Width", __OPT_width)
    go.AddOptionInteger("Height", __OPT_height)
    while True:
        get_rc: Rhino.Input.GetResult = go.Get()
        if go.CommandResult() == Rhino.Commands.Result.Cancel:
            return go.CommandResult()
        if get_rc == Rhino.Input.GetResult.Object:
            break
        elif get_rc == Rhino.Input.GetResult.Cancel:
            return Rhino.Commands.Result.Cancel
        elif get_rc == Rhino.Input.GetResult.Option:
            option = go.Option().EnglishName
            if option == "BuildDirectory":
                folder = rs.BrowseForFolder("Select folder to save the animation")
                if folder:
                    _build_folder = folder
            continue
        break

    go.Get()
    obj_ref = go.Object(0)
    mesh = obj_ref.Mesh()

    _is_saving_gif = __OPT_is_saving_gif.CurrentValue
    _transparent_background = __OPT_transparent_background.CurrentValue
    _fps = __OPT_fps.CurrentValue
    _duration = __OPT_duration.CurrentValue
    _width = __OPT_width.CurrentValue
    _height = __OPT_height.CurrentValue
    num_frames = int(_fps * (_duration / 1000))
    gif_delay = int(1000 / _fps) // 10 
    print("\nOptions values:")
    print(f"\tSaving gif: {_is_saving_gif}")
    print(f"\tTransparent background: {_transparent_background}")
    print(f"\tFPS: {_fps}")
    print(f"\tNumber of frames: {num_frames}")
    print(f"\tGif delay (hundredths secs): {gif_delay}")
    print(f"\tDuration: {_duration}")
    print(f"\tWidth: {_width}")
    print(f"\tHeight: {_height}\n")

    build_folder = os.path.join(_build_folder, "build")
    if os.path.exists(build_folder):
        for file in os.listdir(build_folder):
            os.remove(os.path.join(build_folder, file))
    else:
        os.makedirs(build_folder)

    if _is_saving_gif:
        view = Rhino.RhinoDoc.ActiveDoc.Views.ActiveView
        if view is None:
            raise Exception("No active view found")
        view_capture = Rhino.Display.ViewCapture()
        view_capture.Width = _width
        view_capture.Height = _height
        view_capture.ScaleScreenItems = False
        view_capture.DrawAxes = False
        view_capture.DrawGrid = False
        view_capture.DrawGridAxes = False
        view_capture.TransparentBackground = _transparent_background

    #------------------------------------------------------------
    # Animation + save bitmpas on memory
    #------------------------------------------------------------
    # FIXME: add sub-options for rotation
    total_rotation = 360  # << input (default: 360)

    mu = num_frames // 2
    sigma = num_frames // 6
    gaussian_values = [gaussian(x, mu, sigma) for x in range(num_frames)]
    max_gaussian = max(gaussian_values)
    normalized_gaussian_values = [val / max_gaussian for val in gaussian_values]
    total_gaussian_sum = sum(normalized_gaussian_values)
    normalized_gaussian_values = [val / total_gaussian_sum for val in normalized_gaussian_values]

    total_angle = 0
    mesh_ctr = mesh.GetBoundingBox(True).Center
    for i in range(num_frames):
        angle = normalized_gaussian_values[i] * total_rotation  # scale the angle by the Gaussian value
        total_angle += angle
        xform = rg.Transform.Rotation(math.radians(angle), rg.Vector3d.ZAxis, mesh_ctr)
        mesh.Transform(xform)
        Rhino.RhinoDoc.ActiveDoc.Objects.Replace(obj_ref, mesh)
        Rhino.RhinoDoc.ActiveDoc.Views.Redraw()
        
        if _is_saving_gif:
            bitmap = view_capture.CaptureToBitmap(view)
            if bitmap is None:
                raise Exception("Failed to capture view to bitmap")
            bitmap.Save(os.path.join(build_folder, f"frame_{i}.png"), System.Drawing.Imaging.ImageFormat.Png)
            print_progress_bar(i + 1, num_frames, prefix='Animate:', suffix='Complete')
            rs.Sleep(1)

    rs.UnselectAllObjects()

    #------------------------------------------------------------
    # Bake gif
    #------------------------------------------------------------
    if _is_saving_gif:
        gif_path = os.path.join(build_folder, "animation.gif")
        frames = [os.path.join(build_folder, f"frame_{i}.png") for i in range(num_frames)]
        
        with Image() as new_gif:
            arg2 = library.NewPixelWand()
            library.MagickSetOption(
                new_gif.wand,
                b"dispose",
                b"2"
            )
            for img_path in frames:
                library.MagickReadImage(
                    new_gif.wand,
                    img_path.encode('utf-8')
                )
                new_gif.delay = gif_delay
                print_progress_bar(frames.index(img_path) + 1, len(frames), prefix='Saving:', suffix='Complete')
                rs.Sleep(1)
            Rhino.RhinoApp.SetCommandPrompt("Saving gif, please wait..")
            new_gif.save(filename=gif_path)
            
        for frame in frames:
            os.remove(frame)

        os.system(f"start {gif_path}")
        print(f"Animation saved to: {gif_path}")

    print("Closing moveit.")


if __name__ == "__main__":
    main()