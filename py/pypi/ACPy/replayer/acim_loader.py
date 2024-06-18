import xml.etree.ElementTree as ET


def load(log_file_path):
    tree = ET.parse(log_file_path)
    root = tree.getroot()

    timber = root.find("timber")
    bbox = _parseBBox(timber.find("bbox"))

    cuts = []
    for cutNode in timber.findall("cut"):
        cuts.append(_parseCut(cutNode))
    
    holes = []
    for holeNode in timber.findall("hole"):
        holes.append(_parseHole(holeNode))

    acim_data = {
        "bbox": bbox,
        "cuts": cuts,
        "holes": holes
    }

    return acim_data


def _parseBBox(bboxNode):
    corners = []
    for cornerNode in bboxNode.findall("corner"):
        position = _parsePosition(cornerNode.text)
        id = cornerNode.attrib["id"]

        corners.append((id, position))

    corners.sort(key=lambda x: x[0])
    corners = list(map(lambda x: x[1], corners))

    return corners


def _parseCut(cutNode):
    id = cutNode.attrib["id"]
    faces = []
    for faceNode in cutNode.find("faces").findall("face"):
        id = faceNode.attrib["id"]
        corners = []
        for corner in faceNode.find("corners").findall("corner"):
            corners.append(_parsePosition(corner.text))

        faces.append((id, corners))

    return (id, faces)


def _parseHole(holeNode):
    pass


def _parsePosition(positionString):
    return list(map(float, positionString.split(" ")))
    
    
if __name__ == "__main__":
    from pprint import pprint
    acim_data = load("/Users/petingo/p/augmented-carpentry/py/expirment/mybeam (1).acim")
    pprint(acim_data)
