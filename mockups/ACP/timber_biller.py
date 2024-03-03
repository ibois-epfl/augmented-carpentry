#! python3

import Rhino
import Rhino.Geometry as rg

import Grasshopper as gh
import Grasshopper.Kernel as ghk


if __name__ == "__main__":
    # Grasshopper.DataTree >>> nested list
    nested_ln_filar_model = [i_ln_filarmodel.Branch(i) for i in range(i_ln_filarmodel.BranchCount)]
    nested_dims = [i_beams_dims.Branch(i) for i in range(i_beams_dims.BranchCount)]

    # get total linear length per section
    dict_timber_dims = {  # {[interval dim, [ref_number, total length]}
        rg.Interval(0.2, 0.14): [61201420, 0],
        rg.Interval(0.14, 0.08): [7925785, 0],
        rg.Interval(0.14, 0.14): [61201414, 0],
        rg.Interval(0.08, 0.06): [61130607, 0]
    } 

    for i, ln_i in enumerate(nested_ln_filar_model):
        total_linear_length = 0
        for j, ln_j in enumerate(ln_i):
            total_linear_length += ln_j.Length
        dict_timber_dims[nested_dims[i][0]][1] += total_linear_length
        
    # add a 10% tolerance for each entry
    for key in dict_timber_dims:
        dict_timber_dims[key][1] *= 1.1

    # output
    # round the total length to 2 decimal places
    for key in dict_timber_dims:
        dict_timber_dims[key][1] = round(dict_timber_dims[key][1], 2)
    log_timber_bill = "Timber bill for AC prototype\nCatalog: https://www.getaz-miauton.ch/fileadmin/CrhOneInternet/user_upload/2022-03-02_Massivholz_SR-FR_2022.pdf\n\n"
    for key in dict_timber_dims:
        
        log_timber_bill += f"section: {key} m / serial number: {dict_timber_dims[key][0]} / Total linear length: {dict_timber_dims[key][1]} m\n"
    o_log_timber_bill = log_timber_bill


