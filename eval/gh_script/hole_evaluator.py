#! python3

import math
from datetime import datetime
import csv
import os
import typing

import Rhino
import Rhino.Geometry as rg

import ghpythonlib.treehelpers as th


def truncate_float(value, decimal_places):
    factor = 10 ** decimal_places
    return math.trunc(value * factor) / factor

def get_farthest_faces(faces):
    max_distance = 0
    farthest_pair = (None, None)
    
    # Calculate the center of each face
    centers = [face.GetBoundingBox(True).Center for face in faces]
    
    # Compute the distance between each pair of centers
    for i in range(len(centers)):
        for j in range(i + 1, len(centers)):
            distance = centers[i].DistanceTo(centers[j])
            if distance > max_distance:
                max_distance = distance
                farthest_pair = (faces[i], faces[j])
    
    return farthest_pair

def get_hole_axis(hole) -> typing.Tuple[rg.Vector3d, rg.Point3d, rg.Point3d]:
    faces = hole.Faces
    face1, face2 = get_farthest_faces(faces)
    axis_from = rg.Point3d(face1.GetBoundingBox(True).Center)
    axis_to = rg.Point3d(face2.GetBoundingBox(True).Center)
    if axis_from.Z < axis_to.Z:
        axis_from, axis_to = axis_to, axis_from
    axis = axis_to - axis_from

    return axis, axis_from, axis_to

def main(
    i_out_path,
    i_csv_export,
    i_plate_pln,
    i_gt_holes,
    i_cp_holes
) -> typing.Tuple[
        typing.List[typing.Tuple[rg.Point3d]],
        typing.List[typing.Tuple[rg.Vector3d]]
    ]:
    ## 1) get the axes of the two sets:
    ##    - get the two smallest brepfaces , get their centers, create the vectors
    ## 2) get info of vectors:
    ##    - name/id of the hole
    ##    - drilling angle (gt)
    ## 3) compute the evaluation metrics:
    ##    - 3.a) difference angle
    ##    - 3.b) starting point difference (distance*)
    ##        - the starting point is the center of the ellypse intersection with the place with the plate
    ##    - 3.c) ending point difference (distance between end of vectors)
    ## 4) export everything in a csv file
    
    o_debug = []
    o_axes: typing.List[typing.Tuple[rg.Vector3d]] = []
    o_anchors: typing.List[typing.Tuple[rg.Point3d]] = []

    ## 1) get the axes of the two sets
    gt_holes = i_gt_holes
    cp_holes = i_cp_holes
    gt_axes = []
    gt_anchors = []
    gt_endpoints = []
    cp_axes = []
    cp_anchors = []
    cp_endpoints = []
    for gt_h in gt_holes:
        gt_axis, gt_anchor, gt_endpoint = get_hole_axis(gt_h)
        gt_axes.append(gt_axis)
        gt_anchors.append(gt_anchor)
        gt_endpoints.append(gt_endpoint)
    for cp_h in cp_holes:
        cp_axis, cp_anchor, cp_endpoint = get_hole_axis(cp_h)
        cp_axes.append(cp_axis)
        cp_anchors.append(cp_anchor)
        cp_endpoints.append(cp_endpoint)

    ## 2) get info of vectors
    # name hole
    id_holes: typing.List[str] = []
    alphabet = "abcdefghilmnopqrst"
    for i in range(18):
        for j in range(6):
            id_holes.append(alphabet[i] + str(j + 1))

    # drilling angle
    refrence_vector = rg.Vector3d(0, 0, -1)
    gt_angles = []
    cp_angles = []

    for gt_axis in gt_axes:
        angle = rg.Vector3d.VectorAngle(gt_axis, refrence_vector)
        degree = truncate_float((angle * 180 / 3.141592653589793), 1)
        gt_angles.append(degree)

    for cp_axis in cp_axes:
        angle = rg.Vector3d.VectorAngle(cp_axis, refrence_vector)
        degree = truncate_float((angle * 180 / 3.141592653589793), 1)
        cp_angles.append(degree)

    ## 3) compute the evaluation metrics
    # difference angles
    err_diff_angles = []
    for i in range(len(gt_axes)):
        angle = rg.Vector3d.VectorAngle(gt_axes[i], cp_axes[i])
        degree = truncate_float((angle * 180 / 3.141592653589793), 1)
        err_diff_angles.append(degree)

    # starting point difference
    err_dist_start = []
    for i in range(len(gt_axes)):
        gt_ln = rg.Line(gt_anchors[i], gt_endpoints[i])
        gt_line_param, _ = rg.Intersect.Intersection.LinePlane(gt_ln, i_plate_pln)
        gt_pt_start = gt_ln.PointAt(gt_line_param)
        cp_ln = rg.Line(cp_anchors[i], cp_endpoints[i])
        gt_line_param, _ = rg.Intersect.Intersection.LinePlane(cp_ln, i_plate_pln)
        cp_pt_start = cp_ln.PointAt(gt_line_param)
        err_dist_start.append(gt_pt_start.DistanceTo(cp_pt_start))

    # ending point difference (distance between end of vectors)
    err_dist_end = []
    err_dist_end = [gt_endpoints[i].DistanceTo(cp_endpoints[i]) for i in range(len(gt_endpoints))]

    ## 4) export everything in a csv file
    if i_csv_export:
        if not os.path.exists(i_out_path):
            os.makedirs(i_out_path)

        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        file_name = timestamp + "_hole_evaluation.csv"
        csv_file = os.path.join(i_out_path, file_name)

        with open(csv_file, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Hole ID", "Drilling Angle (GT)", "Drilling Angle (CP)", "Difference Angle (deg)", "Starting Point Difference (m)", "Ending Point Difference (m)"])
            for i in range(len(id_holes)):
                writer.writerow([id_holes[i], gt_angles[i], cp_angles[i], err_diff_angles[i], err_dist_start[i], err_dist_end[i]])

    o_debug = err_diff_angles

    return [gt_axes, cp_axes], [gt_anchors, cp_anchors], o_debug

if __name__ == "__main__":
    o_axes, o_anchors, o_debug = main(
        i_out_path,
        i_csv_export,
        i_plate_pln,
        i_gt_holes,
        i_cp_holes
    )