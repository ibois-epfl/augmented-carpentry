#! python3

import sys
import os
import argparse
import typing

import pandas as pd
pd.set_option('display.max_rows', None)  ## do not truncate in the print

from datetime import datetime
__time_stamp__: str = datetime.now().strftime('%Y%m%d%H%M%S')

import matplotlib.pyplot as plt


def main(
    _path: str,
    _output_path: str
    ) -> None:
    ###################################################################################################
    ## Beams - Joint/JointFaces
    ###################################################################################################
    folder_name_beams: str = "a_beams"
    path_dir_beams: str = os.path.join(_path, folder_name_beams)

    pandas_beams_joints_dataset: pd.DataFrame = pd.DataFrame()
    pandas_beams_joints_dataset['beam_name'] = pd.Series([], dtype=str)

    pandas_beams_jointfaces_dataset: pd.DataFrame = pd.DataFrame()
    pandas_beams_jointfaces_dataset['beam_name'] = pd.Series([], dtype=str)

    for p in os.listdir(path_dir_beams):
        csv_path = os.path.join(path_dir_beams, p, '_csv')
        for f in os.listdir(csv_path):

            if f.endswith('_joint.csv'):
                abs_path_csv = os.path.abspath(os.path.join(csv_path, f))
                pandas_data_beam = pd.read_csv(abs_path_csv)
                pandas_data_beam['beam_name'] = p
                pandas_beams_joints_dataset = pd.concat([pandas_beams_joints_dataset, pandas_data_beam], ignore_index=True)
            if f.endswith('_jointfaces.csv'):
                abs_path_csv = os.path.abspath(os.path.join(csv_path, f))
                pandas_data_beam = pd.read_csv(abs_path_csv)
                pandas_data_beam['beam_name'] = p
                pandas_beams_jointfaces_dataset = pd.concat([pandas_beams_jointfaces_dataset, pandas_data_beam], ignore_index=True)

    # print the pandas data full length
    # print(pandas_beams_joints_dataset)
    print(pandas_beams_jointfaces_dataset)

    # calculate the mean of all distances
    joint_means: typing.List[float] = []
    joint_std: typing.List[float] = []
    # retrieve the value of the column 'mean' and calculate the mean
    for i in range(len(pandas_beams_joints_dataset)):
        rawdata_mean = pandas_beams_joints_dataset['mean'][i]
        rawdata_std = pandas_beams_joints_dataset['std_deviation'][i]
        # if the value is a string do not consider it
        if isinstance(rawdata_mean, str):
            continue
        joint_means.append(rawdata_mean)
        joint_std.append(rawdata_std)
    jointfaces_means: typing.List[float] = []
    # retrieve the value of the column 'mean' and calculate the mean
    for i in range(len(pandas_beams_jointfaces_dataset)):
        rawdata_mean = pandas_beams_jointfaces_dataset['mean'][i]
        # if the value is a string do not consider it
        if isinstance(rawdata_mean, str):
            continue
        jointfaces_means.append(rawdata_mean)

    print(f'Mean of all joint distances: {sum(joint_means) / len(joint_means)}±{sum(joint_std) / len(joint_std)}')
    print(f'Mean of all jointfaces distances: {sum(jointfaces_means) / len(jointfaces_means)}')


    

    ###################################################################################################
    ## Assembly
    ###################################################################################################
    # folder_name_assembly: str = "b_assembly"
    # path_dir_assembly: str = os.path.join(_path, folder_name_assembly)

if __name__ == '__main__':
    def _check_dir_sanity(_path: str) -> bool:
        if not os.path.isdir(_path):
            print(f'Error: {_path} is not a directory')
            return False
        return True

    parser = argparse.ArgumentParser(description='Evaluate the performance of AC')
    parser.add_argument('--path', type=str,
                        help='path to the directory containing the results. This should be the root containing the a_beams and b_assembly folders')
    parser.add_argument('--output_path', type=str, default=f'./',
                        help='path to the directory to save the results')

    args = parser.parse_args()

    _path :str = args.path if _check_dir_sanity(args.path) else sys.exit(1)
    _output_path: str = args.output_path if _check_dir_sanity(args.output_path) else sys.exit(1)

    main(_path,
        _output_path)

