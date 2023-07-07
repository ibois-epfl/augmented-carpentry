import os
import xml.etree.ElementTree as ET

import log
from config import __ACIM_VERSION__

__ACIM_STATE__ = {
                  0: "NotDone",
                  1: "Done",
                  2: "Executed"
            }

class ACIM:
    def __init__(self, out_dir):
        self._out_path_xml = out_dir + ".xml"

        self._root = ET.Element("acim")
        self._root.set("version", __ACIM_VERSION__)
        self._tree = None
        
        self._timber_ets = {}

    def dump_data(self):
        self._prettify(self._root)

        self._tree = ET.ElementTree(self._root)

        self._tree.write(self._out_path_xml, encoding="utf-8", xml_declaration=True)

        # change the extension to .acim
        os.rename(self._out_path_xml, self._out_path_xml.replace(".xml", ".acim"))

    def add_timber(self, guid):
        timber_et = ET.SubElement(self._root, "timber")
        timber_et.set("id", guid)
        self._timber_ets[guid] = timber_et

    def add_timber_state(self, guid, state_value):
        """ Add the execution state of the object, by default False """
        executed_et = ET.SubElement(self._timber_ets[guid], "executed")
        executed_et.text = str(__ACIM_STATE__[state_value])

    def add_bbox(self, guid, corners):
        """
            Add a bounding box to a timber
            :param guid: the guid of the timber
            :param corners: the corners of the bounding box as points
        """
        if len(corners) != 8:
            log.error("BBox must have 8 corners")
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
                 is_start_accessible,
                 is_end_accessible,
                 radius,
                 neighbours=-1,
                 state=__ACIM_STATE__[0]
                 ):
        """
            Add a hole to a timber
            :param guid: the guid of the timber
            :param start_pt: the starting point of the hole
            :param end_pt: the ending point of the hole
            :param is_start_accessible: is the starting point accessible from outside,
            :param is_end_accessible: is the ending point accessible from outside
            :param radius: the radius of the hole
        """

        # print all keys in a dictionnary
        for key in self._timber_ets.keys():
            print(key)

        hole_et = ET.SubElement(self._timber_ets[guid], "hole")
        hole_et.set("id", str(len(self._timber_ets[guid].findall("hole"))))

        state_et = ET.SubElement(hole_et, "state")
        state_et.text = state

        neighbours_et = ET.SubElement(hole_et, "neighbors")
        neighbours_et.text = str(neighbours)

        start_et = ET.SubElement(hole_et, "start")
        accessible_start_et = ET.SubElement(start_et, "accessible")
        accessible_start_et.text = str(is_start_accessible)
        coordinates_start_et = ET.SubElement(start_et, "coordinates")
        coordinates_start_et.text = str(start_pt.X) + " " + str(start_pt.Y) + " " + str(start_pt.Z)

        end_et = ET.SubElement(hole_et, "end")
        accessible_end_et = ET.SubElement(end_et, "accessible")
        accessible_end_et.text = str(is_end_accessible)
        coordinates_end_et = ET.SubElement(end_et, "coordinates")
        coordinates_end_et.text = str(end_pt.X) + " " + str(end_pt.Y) + " " + str(end_pt.Z)

        radius_et = ET.SubElement(hole_et, "radius")
        radius_et.text = str(radius)

    def add_cut(self,
                guid,
                edges,
                faces,
                state=__ACIM_STATE__[0]
    ):
        """
            Add a cut to a timber
            :param guid: the guid of the timber
            :param edges: (List[dict]) the edges of the faces
            :param faces: (List[dict]) the faces of the cut
            :param state: the state of the cut, by default NotDone
        """
        cut_et = ET.SubElement(self._timber_ets[guid], "cut")
        cut_et.set("id", str(len(self._timber_ets[guid].findall("cut"))))

        state_et = ET.SubElement(cut_et, "state")
        state_et.text = state

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

        edges_et = ET.SubElement(cut_et, "edges")
        for e in edges:
            edges_et = ET.SubElement(edges_et, "edge")
            edges_et.set("id", str(e["line_id"]))
            edge_start_et = ET.SubElement(edges_et, "start")
            edge_start_et.text = str(e["start"])
            edge_end_et = ET.SubElement(edges_et, "end")
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