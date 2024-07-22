import System
import Rhino
import os
import scriptcontext as sc
import gc

def capture_img(output_path):
    view = sc.doc.Views.ActiveView
    if view:
        view_capture = Rhino.Display.ViewCapture()
        view_capture.Width = view.ActiveViewport.Size.Width
        view_capture.Height = view.ActiveViewport.Size.Height
        view_capture.ScaleScreenItems = False
        view_capture.DrawAxes = False
        view_capture.DrawGrid = False
        view_capture.DrawGridAxes = False
        view_capture.TransparentBackground = False
        bitmap = view_capture.CaptureToBitmap(view)
        if bitmap:
            bitmap.Save(output_path, System.Drawing.Imaging.ImageFormat.Png)
        del bitmap
        gc.collect()
