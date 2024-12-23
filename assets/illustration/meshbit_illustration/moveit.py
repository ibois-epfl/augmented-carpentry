#! python3
#r: pillow
#r: Wand

import System
import System.Drawing
from enum import Enum

import typing

import math
import sys
import os

from wand.image import Image
from wand.api import library

import Rhino
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs

def _gaussian(x, mu, sigma):
    return (1.0 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2)

def _generate_normalized_gaussian_values(num_frames: int):
    mu = num_frames // 2
    sigma = num_frames // 6
    gaussian_values = [_gaussian(x, mu, sigma) for x in range(num_frames)]
    max_gaussian = max(gaussian_values)
    normalized_gaussian_values = [val / max_gaussian for val in gaussian_values]
    total_gaussian_sum = sum(normalized_gaussian_values)
    normalized_gaussian_values = [val / total_gaussian_sum for val in normalized_gaussian_values]
    return normalized_gaussian_values

def generate_animation_values(num_frames: int, is_gaussian_move: bool, animation_magnitude: float):
    """
        Generate a list of values to animate an object.

        :param num_frames: Number of frames to animate.
        :is_gaussian_move: If True, the animation will be a gaussian move otherwise linear.
        :param animation_magnitude: The magnitude of the animation. This should be the total extent of the animation
        (e.g. total rotation in degrees or total translation distance in units).
        :return: A list of values to animate the object to pass to a transformation function.
    """
    animation_values = []

    if is_gaussian_move:
        normalized_gaussian_values = _generate_normalized_gaussian_values(num_frames)
    else:
        standard_value = 1 / num_frames

    for i in range(num_frames):
        translation = 0
        if is_gaussian_move:
            translation = normalized_gaussian_values[i] * animation_magnitude
        else:
            translation = standard_value * animation_magnitude
        animation_values.append(translation)

    return animation_values

def save_frame(view_capture, view, build_folder, frame_index, num_frames):
    """ Save the Rhino current view of the animation to a bitmap file. """
    bitmap = view_capture.CaptureToBitmap(view)
    if bitmap is None:
        raise Exception("Failed to capture view to bitmap")
    bitmap.Save(os.path.join(build_folder, f"frame_{frame_index}.png"), System.Drawing.Imaging.ImageFormat.Png)
    print_progress_bar(frame_index + 1, num_frames, prefix='Animate:', suffix='Complete')

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

class AnimationType(Enum):
    ROTATION = "rotation"
    TRANSLATION = "translation"


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

    __OPT_rot_degrees = Rhino.Input.Custom.OptionInteger(360, 0, 360)
    __OPT_gaussian_move = Rhino.Input.Custom.OptionToggle(True, "Off", "On")
    __OPT_translation_axis = Rhino.Input.Custom.OptionInteger(2, 0, 2)
    __OPT_translation_distance = Rhino.Input.Custom.OptionDouble(0.1, 0., 10000.)
    __OPT_translation_go_back = Rhino.Input.Custom.OptionToggle(True, "Off", "On")
    
    is_subopt = False
    animation_type = AnimationType.TRANSLATION

    while True:
        if not is_subopt:
            go.ClearCommandOptions()
            go.AddOption("AnimationType", animation_type.name)
            go.AddOptionToggle("isSavingGif", __OPT_is_saving_gif)
            go.AddOptionToggle("TransparentBackground", __OPT_transparent_background)
            go.AddOptionInteger("Fps", __OPT_fps)
            go.AddOptionInteger("Duration_ms", __OPT_duration)
            go.AddOption("BuildDirectory")
            go.AddOptionInteger("Width", __OPT_width)
            go.AddOptionInteger("Height", __OPT_height)
            go.AddOption("Options")

        get_rc: Rhino.Input.GetResult = go.Get()

        if get_rc == Rhino.Input.GetResult.Object:
            break
        elif get_rc == Rhino.Input.GetResult.Cancel:
            if is_subopt:
                is_subopt = False
                continue
            return Rhino.Commands.Result.Cancel

        elif get_rc == Rhino.Input.GetResult.Option:
            option = go.Option().EnglishName
            if option == "BuildDirectory":
                folder = rs.BrowseForFolder("Select folder to save the animation")
                if folder:
                    _build_folder = folder

            elif option == "AnimationType":
                is_subopt = True
                go.ClearCommandOptions()
                go.AddOption(AnimationType.ROTATION.name)
                go.AddOption(AnimationType.TRANSLATION.name)
            elif option == "ROTATION":
                animation_type = AnimationType.ROTATION
                is_subopt = False
                continue
            elif option == "TRANSLATION":
                animation_type = AnimationType.TRANSLATION
                is_subopt = False
                continue

            elif option == "Options":
                is_subopt = True
                go.ClearCommandOptions()
                if animation_type == AnimationType.ROTATION:
                    go.AddOptionInteger("TotalRotation", __OPT_rot_degrees)
                if animation_type == AnimationType.TRANSLATION:
                    go.AddOptionInteger("TranslationAxis", __OPT_translation_axis)
                    go.AddOptionDouble("TranslationDistance", __OPT_translation_distance)
                    go.AddOptionToggle("TranslationGoBack", __OPT_translation_go_back)
                go.AddOptionToggle("GaussianMove", __OPT_gaussian_move)
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
    _total_rotation = __OPT_rot_degrees.CurrentValue
    _is_gaussian_move = __OPT_gaussian_move.CurrentValue
    _translation_axis = rg.Vector3d(0, 0, 0)
    if __OPT_translation_axis.CurrentValue == 0:
        _translation_axis = rg.Vector3d.XAxis
    elif __OPT_translation_axis.CurrentValue == 1:
        _translation_axis = rg.Vector3d.YAxis
    elif __OPT_translation_axis.CurrentValue == 2:
        _translation_axis = rg.Vector3d.ZAxis
    _translation_distance = __OPT_translation_distance.CurrentValue
    _translation_go_back = __OPT_translation_go_back.CurrentValue
    num_frames = int(_fps * (_duration / 1000) / 2) if _translation_go_back else int(_fps * (_duration / 1000))
    gif_delay = int(1000 / _fps) // 10
    sleep_time = _duration / num_frames
    
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
    if animation_type == AnimationType.ROTATION:
        rotation_values = generate_animation_values(
            num_frames,
            _is_gaussian_move,
            _total_rotation
        )

        total_angle = 0
        mesh_ctr = mesh.GetBoundingBox(True).Center
        for i in range(num_frames):
            angle = rotation_values[i]
            total_angle += angle
            xform = rg.Transform.Rotation(math.radians(angle), rg.Vector3d.ZAxis, mesh_ctr)
            mesh.Transform(xform)
            Rhino.RhinoDoc.ActiveDoc.Objects.Replace(obj_ref, mesh)
            Rhino.RhinoDoc.ActiveDoc.Views.Redraw()
            
            if _is_saving_gif:
                save_frame(view_capture, view, build_folder, i, num_frames)
                rs.Sleep(1)

    elif animation_type == AnimationType.TRANSLATION:
        translation_values = generate_animation_values(
            num_frames,
            _is_gaussian_move,
            _translation_distance
        )
        if _translation_go_back:
            backwards = translation_values[::-1]
            backwards = [val * -1 for val in backwards]
            translation_values += backwards
            num_frames *= 2

        total_distance = 0
        for i in range(num_frames):
            translation = translation_values[i]
            total_distance += translation
            xform = rg.Transform.Translation(_translation_axis * translation)
            mesh.Transform(xform)
            Rhino.RhinoDoc.ActiveDoc.Objects.Replace(obj_ref, mesh)
            Rhino.RhinoDoc.ActiveDoc.Views.Redraw()
            
            if _is_saving_gif:
                save_frame(view_capture, view, build_folder, i, num_frames)
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