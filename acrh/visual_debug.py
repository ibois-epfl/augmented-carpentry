import Rhino as rc
import Rhino.Geometry as rg
import scriptcontext as sc
import rhinoscriptsyntax as rs

global __IS_VDEBUG__
__IS_VDEBUG__ = False

def set_on():
    global __IS_VDEBUG__
    __IS_VDEBUG__ = True

def set_off():
    global __IS_VDEBUG__
    __IS_VDEBUG__ = False


def addPt(pt, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddPoint(pt)
        rs.ObjectColor(guid, clr)

def addPtName(pt, name, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddPoint(pt)
        rs.ObjectColor(guid, clr)
        rs.ObjectName(guid, name)

def addBrep(brep, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddBrep(brep)
        rs.ObjectColor(guid, clr)

def addCurve(curve, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddCurve(curve)
        rs.ObjectColor(guid, clr)

def addPolyline(polyline, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddPolyline(polyline)
        rs.ObjectColor(guid, clr)

def addLine(line, clr=(0,0,0)):
    if __IS_VDEBUG__:
        guid = sc.doc.Objects.AddLine(line)
        rs.ObjectColor(guid, clr)

def addSingleDot(pt, txt, clr=(0,0,0)):
    if __IS_VDEBUG__:
        text = str(txt)
        text_GUID = sc.doc.Objects.AddTextDot(text, pt)
        rs.ObjectColor(text_GUID, clr)

def addDotPt(ptA, ptB, txt, clr=(0,0,0)):
    if __IS_VDEBUG__:
        ln = rg.Line(ptA, ptB)
        mid_pt = ln.PointAt(0.5)
        text = str(txt)
        text_GUID = sc.doc.Objects.AddTextDot(text, mid_pt)
        rs.ObjectColor(text_GUID, (0,255,0))
def addDotLn(ln, txt, clr=(0,0,0)):
    if __IS_VDEBUG__:
        mid_pt = ln.PointAt(0.5)
        text = str(txt)
        text_GUID = sc.doc.Objects.AddTextDot(text, mid_pt)
        rs.ObjectColor(text_GUID, (0,255,0))