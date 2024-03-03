#! python3

import Rhino
import Rhino.Geometry as rg

import Grasshopper as gh
import Grasshopper.Kernel as ghk

def non_unique_lines(lst):
    length_counts = {}
    for line in lst:
        length = line.Length
        if length not in length_counts:
            length_counts[length] = [line]
        else:
            length_counts[length].append(line)

    non_unique_lines = [line for lines in length_counts.values() if len(lines) > 1 for line in lines]
    return non_unique_lines

if __name__ == "__main__":
    ln_filar_model = i_ln_filarmodel.AllData()
    
    non_unique_lines = non_unique_lines(ln_filar_model)

    print(non_unique_lines)
    o_not_unique_lines = non_unique_lines
    o_nbr_unique_lines = len(non_unique_lines)