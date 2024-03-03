#! python3

import Rhino
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs

import Grasshopper

def beamerizer(axis, width, height):
    # from an axis line, create a box with a given width and height
    beam_plane_base = rg.Plane(axis.From, axis.Direction)
    beam_interval_xsize = rg.Interval(-width / 2, width / 2)
    beam_interval_ysize = rg.Interval(-height / 2, height / 2)
    beam_interval_zsize = rg.Interval(0, axis.Length)
    beam_box = rg.Box(beam_plane_base, beam_interval_xsize, beam_interval_ysize, beam_interval_zsize)

    return beam_box

def main(
    axis, width: float, height: float
) -> None:
    # convert the datatree to a list of axis
    axis = axis.AllData()


    beams = []
    for ax in axis:
        beams.append(beamerizer(ax, width, height))



    return beams

if __name__ == "__main__":
    print("Running beamerizer.py")
    o_beams = main(i_axis, i_width, i_height)