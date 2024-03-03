#! python3

import Rhino
import Rhino.Geometry as rg


TOL = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance


if __name__ == "__main__":
    # lalbel all the chevrons ends with J1, J2, J3, J4, J5, J6
    pts_chevrons_labels = []
    txt_chevrons_labels = []
    ln_ptsmid_chevrons_labels = []
    ln_txt_chevrons_labels = []
    # use enumerate
    for i, chevron in enumerate(i_ln_chevrons):
        
        pt_start = chevron.PointAt(0)
        pt_end = chevron.PointAt(1)

        if pt_start not in pts_chevrons_labels:
            pts_chevrons_labels.append(pt_start)
            txt_chevrons_labels.append(f"J{i+1}")
        if pt_end not in pts_chevrons_labels:
            pts_chevrons_labels.append(pt_end)
            txt_chevrons_labels.append(f"J0{i+1}")

        ln_ptsmid_chevrons_labels.append(chevron.PointAt(0.5))
        ln_txt_chevrons_labels.append(f"J{i+1}J0{i+1}")
    
    assert len(pts_chevrons_labels) == len(txt_chevrons_labels), "The number of points and labels is not the same"

    o_pts_chevrons_labels = pts_chevrons_labels
    o_txt_chevrons_labels = txt_chevrons_labels
    o_ln_ptsmid_chevrons_labels = ln_ptsmid_chevrons_labels
    o_ln_txt_chevrons_labels = ln_txt_chevrons_labels