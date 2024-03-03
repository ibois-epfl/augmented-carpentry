import System

import Rhino
import Rhino.Geometry as rg

import rhinoscriptsyntax as rs
import scriptcontext

import Grasshopper as gh
import Grasshopper.Kernel as ghk

import math

class Beam:
    def __init__(self,
                 label : str,
                 height : float,
                 width : float,
                 axis_z : rg.Line,
                 clr : System.Drawing.Color = System.Drawing.Color.White
    ):
        """
            Beam class.

                    w    ^       axis y
                    -----|-----
                    |    |    |  h
                    |    |    |
            axis x <|----x    |  axis z
                    |         |
                    |         |
                    |         |
                    -----------

            float height: the height of the beam
            float width: the width of the beam
            rg.Line axis_z: the major axis of the beam
            rg.Line minor_axis: the axis  of the beam
        """
        self.label = label

        self.height = height
        self.width = width
        self._is_rectangular = None

        self.clr = clr

        self._plane : rg.Plane = None
        self._box : rg.Box = None
        self._axis_z : rg.Line = axis_z
        self._axis_x : rg.Line = None
        self._axis_y : rg.Line = None
        self._geometry : dict = None

        self.generate_geometry()

    def generate_geometry(self):
        # if self._axis_y.Length 


        self._plane = rg.Plane(self._axis_z.From, self._axis_z.Direction)
        beam_interval_xsize = rg.Interval(-self.width / 2, self.width / 2)
        beam_interval_ysize = rg.Interval(-self.height / 2, self.height / 2)
        beam_interval_zsize = rg.Interval(0, self._axis_z.Length)
        self._box = rg.Box(
            self._plane,
            beam_interval_xsize,
            beam_interval_ysize,
            beam_interval_zsize)
        self._axis_x = rg.Line(
            self._axis_z.From,
            self._axis_z.From + self._plane.YAxis * self.height/2
        )
        self._axis_y = rg.Line(
            self._axis_z.From,
            self._axis_z.From + self._plane.XAxis * self.width/2
        )

        # if sekf._axis_x is bigger than self._axis_y, invert the values
        if self._axis_x.Length > self._axis_y.Length:
            self._axis_x, self._axis_y = self._axis_y, self._axis_x

        #check if the piece is rectangular
        if not self.is_rectangular:
            print(f"element {self.label} is not rectangular")
            return
        
        # # # check if the box is placed with the axis z upwards
        all_positive = lambda x: x if x > 0 else -x
        # if all_positive(self._axis_x.To.Z) > all_positive(self._axis_y.To.Z):
        #     print(f"element {self.label} is not placed with the axis z upwards")
        #     self.rotate(90, self._axis_z.Direction, self._axis_z.From)

        # check that the axis_y is pointing upwards
        # angle_worldZ_axisY = rg.Vector3d.VectorAngle(rg.Vector3d.ZAxis, self._axis_y.Direction)
        # deg_angle_worldZ_axisY = angle_worldZ_axisY * (180 / 3.141592653589793)

        # print(f"element {self.label} angle with world z axis: {deg_angle_worldZ_axisY}")
        # if deg_angle_worldZ_axisY > 90 or deg_angle_worldZ_axisY < 270:
        #     # print(f"element {self.label} is not placed with the axis y upwards")
        #     self.rotate(90, self._axis_z.Direction, self._axis_z.From)

        if all_positive(self._axis_y.Direction.Z) < all_positive(self._axis_y.Direction.X) or all_positive(self._axis_y.Direction.Z) < all_positive(self._axis_y.Direction.Y):
            self.rotate(90, self._axis_z.Direction, self._axis_z.From)



        # # elif self._axis_Z.Direction.Z < 0:
        # #     print(f"element {self.label} is placed with the axis z downwards")

        # #     self.rotate(90, self._axis_z.Direction, self._axis_z.From)

    def rotate(self, angle_deg : float, axis : rg.Vector3d, rot_cemter : rg.Point3d):
        """
        Rotate the beam around the axis by the angle in degrees
        """
        rad_2_deg = angle_deg * (3.141592653589793 / 180)
        x_rot = rg.Transform.Rotation(rad_2_deg, axis, rot_cemter)
        self._box.Transform(x_rot)
        self._axis_x.Transform(x_rot)
        self._axis_y.Transform(x_rot)
        self._axis_z.Transform(x_rot)

    def bake(self, layer_name : str):
        active_doc = Rhino.RhinoDoc.ActiveDoc

        white_clr = System.Drawing.Color.White
        red_clr = System.Drawing.Color.Red
        blue_clr = System.Drawing.Color.Blue
        green_clr = System.Drawing.Color.Green

        label_beam = self.label

        # create the layer structure
        scriptcontext.doc = Rhino.RhinoDoc.ActiveDoc

        super_super_layer = "ACP"
        super_layer = f"{super_super_layer}::{layer_name}"
        sub_layer = f"{super_layer}::Beam_{label_beam}"
        sub_sub_layer_boxes = f"{sub_layer}::Geometry"
        sub_sub_layer_axes = f"{sub_layer}::Axes"
        sub_sub_layer_dot = f"{sub_layer}::Dot"

        if not rs.IsLayer(super_layer):
            rs.AddLayer(super_layer)
        rs.AddLayer(sub_layer, white_clr, True, False)
        rs.AddLayer(sub_sub_layer_boxes, white_clr, True, False)
        rs.AddLayer(sub_sub_layer_axes, white_clr, True, False)
        rs.AddLayer(sub_sub_layer_dot, white_clr, True, False)

        # Geometries
        beam_brep = self._box.ToBrep()
        object_beam_brep_attributes = Rhino.DocObjects.ObjectAttributes()
        object_beam_brep_attributes.ColorSource = Rhino.DocObjects.ObjectColorSource.ColorFromObject
        object_beam_brep_attributes.ObjectColor = self.clr
        object_beam_brep_attributes.Name = f"beam_box_{self.label}"
        object_beam_brep_attributes.LayerIndex = scriptcontext.doc.Layers.FindByFullPath(sub_sub_layer_boxes, -1)
        beam_brep_id = active_doc.Objects.AddBrep(beam_brep, object_beam_brep_attributes)

        # Axis
        beam_axisX = self._axis_x.ToNurbsCurve()
        object_beam_axisX_attributes = Rhino.DocObjects.ObjectAttributes()
        object_beam_axisX_attributes.ColorSource = Rhino.DocObjects.ObjectColorSource.ColorFromObject
        object_beam_axisX_attributes.ObjectColor = red_clr
        object_beam_axisX_attributes.Name = f"beam_axisX_{self.label}"
        object_beam_axisX_attributes.LayerIndex = scriptcontext.doc.Layers.FindByFullPath(sub_sub_layer_axes, -1)
        beam_axisX_id = active_doc.Objects.AddCurve(beam_axisX, object_beam_axisX_attributes)

        beam_axisY = self._axis_y.ToNurbsCurve()
        object_beam_axisY_attributes = Rhino.DocObjects.ObjectAttributes()
        object_beam_axisY_attributes.ColorSource = Rhino.DocObjects.ObjectColorSource.ColorFromObject
        object_beam_axisY_attributes.ObjectColor = green_clr
        object_beam_axisY_attributes.Name = f"beam_axisY_{self.label}"
        object_beam_axisY_attributes.LayerIndex = scriptcontext.doc.Layers.FindByFullPath(sub_sub_layer_axes, -1)
        beam_axisY_id = active_doc.Objects.AddCurve(beam_axisY, object_beam_axisY_attributes)

        beam_axisZ = self._axis_z.ToNurbsCurve()
        object_beam_axisZ_attributes = Rhino.DocObjects.ObjectAttributes()
        object_beam_axisZ_attributes.ColorSource = Rhino.DocObjects.ObjectColorSource.ColorFromObject
        object_beam_axisZ_attributes.ObjectColor = blue_clr
        object_beam_axisZ_attributes.Name = f"beam_axisZ_{self.label}"
        object_beam_axisZ_attributes.LayerIndex = scriptcontext.doc.Layers.FindByFullPath(sub_sub_layer_axes, -1)
        beam_axisZ_id = active_doc.Objects.AddCurve(beam_axisZ, object_beam_axisZ_attributes)

        # Dot
        center_beam = beam_brep.GetBoundingBox(True).Center
        dot = Rhino.Geometry.TextDot(self.label, center_beam)
        object_dot_attributes = Rhino.DocObjects.ObjectAttributes()
        object_dot_attributes.ColorSource = Rhino.DocObjects.ObjectColorSource.ColorFromObject
        object_dot_attributes.ObjectColor = white_clr
        object_dot_attributes.Name = f"dot_{self.label}"
        object_dot_attributes.LayerIndex = scriptcontext.doc.Layers.FindByFullPath(sub_sub_layer_dot, -1)
        dot_id = active_doc.Objects.AddTextDot(dot, object_dot_attributes)

        # create a group for the beam
        index = active_doc.Groups.Add([
            beam_brep_id,
            beam_axisX_id,
            beam_axisY_id,
            beam_axisZ_id,
            dot_id
        ])

        ghdoc = gh.GH_InstanceServer.DocumentServer
        scriptcontext.doc = ghdoc


    def __repr__(self):
        return f"Beam({self._axis_z}, {self.minor_axis}, {self.length}, {self.width})"

    @property
    def geometry(self):
        return self._box, self._axis_x, self._axis_y, self._axis_z, self.label, self.clr

    @property
    def is_rectangular(self):
        self._is_rectangular = self.height != self.width
        return self._is_rectangular