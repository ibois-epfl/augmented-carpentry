#! python3

import System
import Rhino
import Rhino.Geometry as rg

import rhinoscriptsyntax as rs

import Grasshopper as gh
import Grasshopper.Kernel as ghk

from beam import Beam


if __name__ == "__main__":
    # convert the Grasshopper.DataTree to a nested lines based on the branches
    ln_filar_model = i_ln_filarmodel.AllData()
    ln_labels = i_ln_labels.AllData()
    heights = i_height.AllData()
    widths = i_width.AllData()
    clrs = i_clr.AllData()
    layer_names = i_layer_name.AllData()

    beams = []
    for i, ln in enumerate(ln_filar_model):
        beam = Beam(ln_labels[i], heights[i], widths[i], ln, clrs[i])
        beams.append(beam)

    # preview
    o_beams_box = [beam.geometry[0] for beam in beams]
    o_beams_axisX = [beam.geometry[1] for beam in beams]
    o_beams_axisY = [beam.geometry[2] for beam in beams]
    o_beams_axisZ = [beam.geometry[3] for beam in beams]
    o_beams_labels = [beam.geometry[4] for beam in beams]
    o_beams_clr = [beam.geometry[5] for beam in beams]

    # bake the boxes
    if i_is_bake:
        for i, beam in enumerate(beams):
            beam.bake(layer_names[i])