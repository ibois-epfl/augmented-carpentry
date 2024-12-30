import os
import sys
import xml.etree.ElementTree as ET

# import log
# from config import __ACIM_VERSION__


__ACIM_STATE__ = {
                  0: "NotDone",
                  1: "Done",
            }

class ACIM:
    def __init__(self, 
        out_dir : str,
        out_name : str
        ):
        self._out_path_xml = os.path.join(out_dir, out_name) + ".acim"

        self._root = ET.Element("acim")
        # self._root.set("version", __ACIM_VERSION__)
        self._tree = None
        
        self._timber_ets = {}

    def dump_data(self, is_overwrite=False):
        self._prettify(self._root)
        self._tree = ET.ElementTree(self._root)
        # check if the file exists
        if os.path.isfile(self._out_path_xml):
            if is_overwrite:
                os.remove(self._out_path_xml)
            else:
                return
        self._tree.write(self._out_path_xml, encoding="utf-8", xml_declaration=True)

    def add_timber(self, guid):
        timber_et = ET.SubElement(self._root, "timber")
        timber_et.set("id", guid)
        self._timber_ets[guid] = timber_et
        timber_state_et = ET.SubElement(timber_et, "state")
        timber_state_et.text = str(__ACIM_STATE__[0])
        timber_current_et = ET.SubElement(timber_et, "current")
        timber_current_et.text = "__NOT_SET__"

    def add_timber_state(self, guid, state_value):
        """ Add the execution state of the object, by default False """
        state_et = ET.SubElement(self._timber_ets[guid], "state")
        state_et.text = str(__ACIM_STATE__[state_value])

    def add_bbox(self, guid, corners):
        """
            Add a bounding box to a timber
            :param guid: the guid of the timber
            :param corners: the corners of the bounding box as points
        """
        if len(corners) != 8:
            # print("BBox must have 8 corners")
            return
        bbox_et = ET.SubElement(self._timber_ets[guid], "bbox")
        for i, corner in enumerate(corners):
            corner_et = ET.SubElement(bbox_et, "corner")
            corner_et.set("id", str(i))
            val_x = str(corner.X)
            val_y = str(corner.Y)
            val_z = str(corner.Z)
            corner_et.text = val_x + " " + val_y + " " + val_z
    
    def add_hole(self, 
                 guid,
                 start_pt,
                 end_pt,
                 is_start_exposed,
                 is_end_exposed,
                 radius,
                 neighbours=-1,
                 state=__ACIM_STATE__[0]
                 ):
        """
            Add a hole to a timber
            :param guid: the guid of the timber
            :param start_pt: the starting point of the hole
            :param end_pt: the ending point of the hole
            :param is_start_exposed: is the starting point accessible from outside,
            :param is_end_exposed: is the ending point accessible from outside
            :param radius: the radius of the hole
        """
        hole_et = ET.SubElement(self._timber_ets[guid], "hole")
        hole_id_nbr = str(len(self._timber_ets[guid].findall("hole")))
        hole_id = "Hole#" + hole_id_nbr
        hole_et.set("id", hole_id)

        state_et = ET.SubElement(hole_et, "state")
        state_et.text = state

        neighbours_et = ET.SubElement(hole_et, "neighbors")
        neighbours_et.text = str(neighbours)

        start_et = ET.SubElement(hole_et, "start")
        exposed_start_et = ET.SubElement(start_et, "exposed")
        exposed_start_et.text = str(is_start_exposed)
        coordinates_start_et = ET.SubElement(start_et, "coordinates")
        coordinates_start_et.text = str(start_pt.X) + " " + str(start_pt.Y) + " " + str(start_pt.Z)

        end_et = ET.SubElement(hole_et, "end")
        exposed_end_et = ET.SubElement(end_et, "exposed")
        exposed_end_et.text = str(is_end_exposed)
        coordinates_end_et = ET.SubElement(end_et, "coordinates")
        coordinates_end_et.text = str(end_pt.X) + " " + str(end_pt.Y) + " " + str(end_pt.Z)

        radius_et = ET.SubElement(hole_et, "radius")
        radius_et.text = str(radius)

    def add_cut(self,
                guid,
                center,
                edges,
                faces,
                state=__ACIM_STATE__[0]
    ):
        """
            Add a cut to a timber
            :param guid: the guid of the timber
            :param center: (String) the centroid point of the polysurface cut
            :param edges: (List[dict]) the edges of the faces
            :param faces: (List[dict]) the faces of the cut
            :param state: the state of the cut, by default NotDone
        """
        cut_et = ET.SubElement(self._timber_ets[guid], "cut")
        cut_id_nbr = str(len(self._timber_ets[guid].findall("cut")))
        cut_id = "Cut#" + cut_id_nbr
        cut_et.set("id", cut_id)

        state_et = ET.SubElement(cut_et, "state")
        state_et.text = state

        center_et = ET.SubElement(cut_et, "center")
        center_et.text = center

        faces_et = ET.SubElement(cut_et, "faces")
        for f in faces:
            face_et = ET.SubElement(faces_et, "face")
            face_et.set("id", str(f["face_id"]))
            face_state_et = ET.SubElement(face_et, "state")
            face_state_et.text = state
            face_exposed_et = ET.SubElement(face_et, "exposed")
            face_exposed_et.text = str(f["exposed"])
            face_edges_et = ET.SubElement(face_et, "edges")
            face_edges_et.text = str(f["edges"])
            face_corners_et = ET.SubElement(face_et, "corners")
            for idx, c in enumerate(f["corners"]):
                corner_et = ET.SubElement(face_corners_et, "corner")
                corner_et.set("id", str(idx))
                corner_et.text = str(c)

        edges_et = ET.SubElement(cut_et, "edges")
        for e in edges:
            edge_et = ET.SubElement(edges_et, "edge")
            edge_et.set("id", str(e["line_id"]))
            edge_start_et = ET.SubElement(edge_et, "start")
            edge_start_et.text = str(e["start"])
            edge_end_et = ET.SubElement(edge_et, "end")
            edge_end_et.text = str(e["end"])

    def peek_current_hole_id(self, guid):
        """ Get the last hole id of a timber """
        return (len(self._timber_ets[guid].findall("hole"))+1)

    def _prettify(self, elem, level=0):
        """ Pretty print XML tree with blocks and indents """
        indent_spaces = "    "
        i = "\n" + level * indent_spaces
        if len(elem):
            if not elem.text or not elem.text.strip():
                elem.text = i + indent_spaces
            if not elem.tail or not elem.tail.strip():
                elem.tail = i
            for subelem in elem:
                self._prettify(subelem, level + 1)
            if not elem.tail or not elem.tail.strip():
                elem.tail = i
        else:
            if level and (not elem.tail or not elem.tail.strip()):
                elem.tail = i
