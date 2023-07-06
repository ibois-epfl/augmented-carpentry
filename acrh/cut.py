import Rhino as rc
import Rhino.Geometry as rg
import rhinoscriptsyntax as rs
import scriptcontext as sc

import log
import util

# TODO: to implement
def parse_data_from_brep(ACIM,
                         p_GUID,
                         cut_b,
                         bbox_b):
    """
        Parse data from a brep defining a cut
        :param ACIM: the ACIM object to export xml
        :param p_GUID: the guid of the timber
        :param box_b: the brep defining the cut
        :param bbox_b: the brep of the bounding box
    """
    log.info(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
    log.info("Parsing cut data..")
    bbox_faces_b = util.explode_brep(bbox_b)
    cut_faces_b = util.explode_brep(cut_b)
    log.info("Cut faces: " + str(len(cut_faces_b)))
    # >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>