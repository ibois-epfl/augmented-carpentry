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
import numpy as np


def clean_missing_data(df: pd.DataFrame) -> pd.DataFrame:
    """
    Remove rows with missing data in the mean column.

    Args:
        df (pd.DataFrame): The DataFrame to clean.

    Returns:
        pd.DataFrame: The DataFrame with rows with missing data removed.
    """
    df_clean = pd.DataFrame()
    for i in range(len(df)):
        rawmean_data = df['mean'][i]
        if isinstance(rawmean_data, str):
            continue
        df_clean = df_clean.append(df.iloc[i], ignore_index=True)
    df_clean.reset_index(drop=True, inplace=True)

    return df_clean

def process_joint_face_id(df: pd.DataFrame, joint_face_id_col: str, beam_col: str) -> pd.DataFrame:
    """
    Process the joint_face_id column to extract joint label, joint face label, and total number of joint faces per joint per beam.
    And removes the joint_face id column since it is no longer needed.

    Args:
        df (pd.DataFrame): The DataFrame containing the joint_face_id column and the beam column.
        joint_face_id_col (str): The name of the column containing the joint_face_id.
        beam_col (str): The name of the column containing the beam index.

    Returns:
        pd.DataFrame: The DataFrame with new columns for joint label, joint face label, and total number of joint faces per joint per beam.
    """
    df[['joint_label', 'joint_face_label']] = df[joint_face_id_col].str.split('--', expand=True)[[1, 2]]
    face_counts = df.groupby([beam_col, 'joint_label'])['joint_face_label'].transform('nunique')
    df['joint_face_count'] = face_counts
    df.drop(columns=[joint_face_id_col], inplace=True)

    return df

def remove_single_joint_faces(df: pd.DataFrame, joint_label_col: str, beam_col: str) -> pd.DataFrame:
    """
    Remove all rows where there is only a single joint face per joint. We do this because in our analysis methodology, every joint is registered
    to the CAD joint model and if there is only one face the results would be perfect anyways because we would registering a plane to a plane.

    Args:
        df (pd.DataFrame): The DataFrame containing the joint label and beam columns.
        joint_label_col (str): The name of the column containing the joint label.
        beam_col (str): The name of the column containing the beam index.

    Returns:
        pd.DataFrame: The DataFrame with rows removed where there is only a single joint face per joint.
    """
    df = df[df['joint_face_count'] > 1]
    df.reset_index(drop=True, inplace=True)

    return df


def main(
    _path: str,
    _output_path: str
    ) -> None:
    ###################################################################################################
    ## Beams - Joint/JointFaces
    ###################################################################################################
    # ======= importing data into memory =======
    folder_name_beams: str = "a_beams"
    path_dir_beams: str = os.path.join(_path, folder_name_beams)

    df_joints_dataset: pd.DataFrame = pd.DataFrame()
    df_joints_dataset['beam_name'] = pd.Series([], dtype=str)

    df_jointfaces_dataset: pd.DataFrame = pd.DataFrame()
    df_jointfaces_dataset['beam_name'] = pd.Series([], dtype=str)

    for p in os.listdir(path_dir_beams):
        csv_path = os.path.join(path_dir_beams, p, '_csv')
        for i, f in enumerate(os.listdir(csv_path)):
            if f.endswith('.csv'):
                abs_path_csv = os.path.abspath(os.path.join(csv_path, f))
                pandas_data_beam = pd.read_csv(abs_path_csv)
                pandas_data_beam['beam_name'] = p
                if f.endswith('_joint.csv'):
                    df_joints_dataset = pd.concat([df_joints_dataset, pandas_data_beam], ignore_index=True)
                elif f.endswith('_jointfaces.csv'):
                    df_jointfaces_dataset = pd.concat([df_jointfaces_dataset, pandas_data_beam], ignore_index=True)

    # ======= joint analysis =======
    df_joints_dataset = clean_missing_data(df_joints_dataset)

    err_joint_mean = np.mean(np.array(df_joints_dataset['mean'].tolist()))
    err_joint_std = np.mean(np.array(df_joints_dataset['std_deviation'].tolist()))
    err_joint_total_nbr = len(df_joints_dataset)

    # ======= jointfaces analysis =======
    df_jointfaces_dataset = process_joint_face_id(df_jointfaces_dataset, 'joint_face id', 'beam_name')
    df_jointfaces_dataset = remove_single_joint_faces(df_jointfaces_dataset, 'joint_label', 'beam_name')
    df_jointfaces_dataset = clean_missing_data(df_jointfaces_dataset)

    err_jointface_mean = np.mean(np.array(df_jointfaces_dataset['mean'].tolist()))
    err_jointface_std = np.mean(np.array(df_jointfaces_dataset['std_deviation'].tolist()))

    print(f"Total number of joint distances: {err_joint_total_nbr}")
    print(f"Mean of all joint distances: {err_joint_mean}±{err_joint_std}")
    print(f"Mean of all jointfaces distances: {err_jointface_mean}±{err_jointface_std}")


    ###################################################################################################
    ## Assembly
    ###################################################################################################
    # folder_name_assembly: str = "b_assembly"
    # path_dir_assembly: str = os.path.join(_path, folder_name_assembly)

    ## TODO: here we need to filter the too high values by capping the values farther than 5cm for example 
    # due to an inaxitude of measuring of DF

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

