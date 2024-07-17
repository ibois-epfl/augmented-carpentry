import Rhino
import ghpythonlib.components as ghcomp

import xml.etree.ElementTree as ET

from acim_data import ACIMData

scale = 50
tolerance = 0.01

def load(acim_path):
    tree = ET.parse(acim_path)
    root = tree.getroot()

    timber = root.find("timber")
    bbox = _parse_bbox(timber.find("bbox"))

    cuts = {}
    for cutNode in timber.findall("cut"):
        id, faces = _parse_cut(cutNode)
        cuts[id] = faces
    
    holes = {}
    for holeNode in timber.findall("hole"):
        id, cylinder = _parse_hole(holeNode)
        holes[id] = cylinder

    acim_data = ACIMData(bbox, cuts, holes)

    return acim_data


def _parse_bbox(bboxNode):
    corners = []
    for cornerNode in bboxNode.findall("corner"):
        position = _parse_position(cornerNode.text)
        id = int(cornerNode.attrib["id"])

        corners.append((id, position))

    corners.sort(key=lambda x: x[0])
    corners = list(map(lambda x: x[1], corners))

    # bbox, _ = Rhino.Geometry.Mesh.CreateConvexHull3D(corners, tolerance, tolerance)

    faces = []
    faces_indices = [
        [0, 3, 2, 1],
        [4, 5, 6, 7],
        [0, 1, 5, 4],
        [3, 7, 6, 2],
        [0, 4, 7, 3],
        [1, 2, 6, 5]
    ]
    for indices in faces_indices:
        face = ghcomp.x4PointSurface(corners[indices[0]], corners[indices[1]], corners[indices[2]], corners[indices[3]])
        faces.append(face)
    
    bbox = Rhino.Geometry.Brep.MergeBreps(faces, tolerance)

    return bbox


def _parse_cut(cutNode):
    id = cutNode.attrib["id"]
    faces = []
    for faceNode in cutNode.find("faces").findall("face"):
        corner_id = int(faceNode.attrib["id"])
        corners = []
        for corner in faceNode.find("corners").findall("corner"):
            corners.append(_parse_position(corner.text))

        boundary = Rhino.Geometry.Polyline(corners + [corners[0]])
        face = ghcomp.FragmentPatch(boundary)
        faces.append(face)

    cutBrep = Rhino.Geometry.Brep.MergeBreps(faces, tolerance)

    return (id, cutBrep)


def _parse_hole(holeNode):
    id = holeNode.attrib["id"]
    radius = float(holeNode.find("radius").text) * scale
    start = _parse_position(holeNode.find("start").find("coordinates").text)
    end = _parse_position(holeNode.find("end").find("coordinates").text)
    
    if start.Z > end.Z:
        start, end = end, start

    vec = end - start
    
    basePlane = Rhino.Geometry.Plane(start, vec)
    circle = Rhino.Geometry.Circle(basePlane, radius)
    cylinder = Rhino.Geometry.Cylinder(circle, vec.Length).ToBrep(True, True)
    
    return (id, cylinder)


def _parse_position(positionString):
    x, y, z = tuple(map(float, positionString.split(" ")))
    x *= scale
    y *= scale
    z *= scale
    return Rhino.Geometry.Point3d(x, y, z)
    
    
if __name__ == "__main__":
    from pprint import pprint
    acim_data = load("/Users/petingo/p/augmented-carpentry/py/expirment/all_log/Z4Z2_2024-5-27-16-40-21/AC_info_model.acim")
    pprint(acim_data)

    bbox = acim_data.bbox

    all_cut_faces = []
    for _, faces in acim_data.cuts.items():
        all_cut_faces.append(faces)

    all_holes = []
    for _, cylinder in acim_data.holes.items():
        all_holes.append(cylinder)