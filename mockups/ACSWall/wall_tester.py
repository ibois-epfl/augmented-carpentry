#! python3

import Rhino
import Rhino.Geometry as rg


if __name__ == "__main__":
    # print("Hello World!")

    o_axis_vectors = []
    o_pts_A = []
    o_pts_B = []


    # divide the line i_ln_Z into 10 segments
    o_ln_Z = i_ln_Z.ToNurbsCurve()
    res = o_ln_Z.DivideByCount(10, True, o_axis_vectors)
    print(res)

    # for i in range(len(o_axis_vectors)):
    #     o_pts_A.append(o_ln_Z.PointAt(o_axis_vectors[i]))
    #     o_pts_B.append(o_ln_Z.PointAt(o_axis_vectors[i]+0.1))
    # print(o_pts_A)