#! python3

import sys
import os
import argparse
import typing

from tqdm import tqdm

import pandas as pd
pd.set_option('display.max_rows', None)  ## do not truncate in the print

from datetime import datetime
__time_stamp__: str = datetime.now().strftime('%Y%m%d%H%M%S')

import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
from mpl_toolkits.mplot3d import Axes3D

import numpy as np

import open3d as o3d

"""
        TODO:
        --> load assembly in memory for assembly
        --> representation for assembly
        --> compute rrors for the drilling holes
    """


def clean_missing_data(df: pd.DataFrame) -> pd.DataFrame:
    """
    Remove rows with missing data in the mean column.

    Args:
        df (pd.DataFrame): The DataFrame to clean.

    Returns:
        pd.DataFrame: The DataFrame with rows with missing data removed.
    """
    df_clean = pd.DataFrame()
    for i in (pbar := tqdm(range(len(df)))):
        pbar.set_description(f"Cleaning missing data")
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
    to the CAD joint model and if there is only one face the results would be overfitting anyways because we would registering a plane to a plane.

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
    paths: typing.List[str],
    output_path: str
    ) -> None:
    ###################################################################################################
    ## Beams - Joint/JointFaces
    ###################################################################################################
    # =================================================================================================
    # importing data into memory
    folder_name_beams: str = "a_beams"
    folder_name_assembly: str = "b_assembly"

    df_joints_dataset: pd.DataFrame = pd.DataFrame()
    df_joints_dataset['beam_name'] = pd.Series([], dtype=str)

    df_jointfaces_dataset: pd.DataFrame = pd.DataFrame()
    df_jointfaces_dataset['beam_name'] = pd.Series([], dtype=str)

    df_assessment_dataset: pd.DataFrame = pd.DataFrame()


    # TODO: add for the assembly

    path_csvs_beams: typing.List[str] = []

    for i, p in (pbar := tqdm(enumerate(paths))):
        pbar.set_description(f"Loading csv into memory.")
        path_dir_beams: str = os.path.join(p, folder_name_beams)
        # joint loading
        for p_beam in os.listdir(path_dir_beams):
            csv_path = os.path.join(path_dir_beams, p_beam)
            for i, f in enumerate(os.listdir(csv_path)):
                if f.endswith('.csv'):
                    abs_path_csv = os.path.abspath(os.path.join(csv_path, f))
                    pandas_data_beam = pd.read_csv(abs_path_csv)
                    pandas_data_beam['beam_name'] = p_beam
                    if f.endswith('_joint.csv'):
                        df_joints_dataset = pd.concat([df_joints_dataset, pandas_data_beam], ignore_index=True)
                    elif f.endswith('_jointfaces.csv'):
                        df_jointfaces_dataset = pd.concat([df_jointfaces_dataset, pandas_data_beam], ignore_index=True)
        # assembly loading
        # FIXME: load assembly data online
        path_dir_assembly = os.path.join(p, folder_name_assembly)
        # for p_assembly in os.listdir(path_dir_assembly):
        #     csv_path = os.path.join(path_dir_assembly, p_assembly)
        #     for i, f in enumerate(os.listdir(csv_path)):
        #         if f.endswith('.csv'):
        #             abs_path_csv = os.path.abspath(os.path.join(csv_path, f))
        #             pandas_data_beam = pd.read_csv(abs_path_csv)
        #             df_assessment_dataset = pd.concat([df_assessment_dataset, pandas_data_beam], ignore_index=True)

    print(f"{'<' * 100}\n{'Data loaded'}\n{'<' * 100}")

    # =================================================================================================
    # joint analysis
    df_joints_dataset = clean_missing_data(df_joints_dataset)

    df_joints_dataset['mean'] = df_joints_dataset['mean'] * 1000
    err_joint_mean = np.mean(np.array(df_joints_dataset['mean'].tolist()))
    df_joints_dataset['std_deviation'] = df_joints_dataset['std_deviation'] * 1000
    err_joint_std = np.mean(np.array(df_joints_dataset['std_deviation'].tolist()))
    err_joint_total_nbr = len(df_joints_dataset)

    err_beam_lengths = np.array(df_joints_dataset['beam_length'].tolist())
    err_joint_distances_to_beam_midpoint = np.array(df_joints_dataset['joint_distance_to_beam_midpoint'].tolist())


    # =================================================================================================
    # jointfaces analysis
    df_jointfaces_dataset = process_joint_face_id(df_jointfaces_dataset, 'joint_face id', 'beam_name')
    df_jointfaces_dataset = remove_single_joint_faces(df_jointfaces_dataset, 'joint_label', 'beam_name')
    df_jointfaces_dataset = clean_missing_data(df_jointfaces_dataset)

    df_jointfaces_dataset['mean'] = df_jointfaces_dataset['mean'] * 1000
    err_jointface_mean = np.mean(np.array(df_jointfaces_dataset['mean'].tolist()))
    df_jointfaces_dataset['std_deviation'] = df_jointfaces_dataset['std_deviation'] * 1000
    err_jointface_std = np.mean(np.array(df_jointfaces_dataset['std_deviation'].tolist()))
    err_jointface_total_nbr = len(df_jointfaces_dataset)

    ###################################################################################################
    ## Printing
    ###################################################################################################
    num_chars = 100
    print(f"{'-' * num_chars}\n{'joint analysis'}\n{'-' * num_chars}")

    print(f"{'Total number of joints evaluated:':<40} {err_joint_total_nbr:<20} {'#'}")
    print(f"{'Average beam length:':<40} {np.mean(err_beam_lengths):<20.3f} {'m'}")
    print(f"{'Average distance to beam midpoint:':<40} {np.mean(err_joint_distances_to_beam_midpoint):<20.3f} {'m'}")

    print(f"{'Average number of faces per joint:':<40} {np.mean(df_jointfaces_dataset['joint_face_count']):<20.0f} {'#'}")

    err_joint_mean_std_str = f"{err_joint_mean:.1f}" + " ± " + f"{err_joint_std:.1f}"
    err_jointface_mean_std_str = f"{err_jointface_mean:.1f}" + " ± " + f"{err_jointface_std:.1f}"
    print(f"{'Mean of all joint distance error:':<40} {err_joint_mean_std_str:<20} {'mm'}")
    print(f"{'Mean of all jointfaces distance error:':<40} {err_jointface_mean_std_str:<20} {'mm'}")


    ###################################################################################################
    ## Printing
    ###################################################################################################
    # -----------------------------------------------------------------------------------------------
    # Joint position error - beam length
    # -----------------------------------------------------------------------------------------------
    # take the range between the smallest and the largest beam length and make 8 bins
    bins = np.linspace(np.min(err_beam_lengths), np.max(err_beam_lengths), 8)
    labels = [f'{bins[i+1]:.1f}' for i in range(len(bins)-1)]
    df_joints_dataset['beam_length_bin'] = pd.cut(df_joints_dataset['beam_length'], bins=bins, labels=labels)

    clr_markers = 'red'
    flierprops: dict =  dict(marker='+', markeredgecolor=clr_markers, markersize=9)
    boxprops = dict(linewidth=0.9, color='blue')
    whiskerprops = dict(linewidth=0.9, linestyle=(0, (10, 10)), color='black')
    medianprops = dict(color=clr_markers)
    pad = 8
    labelpad_y = 2

    fig, axs = plt.subplots(1, 3, figsize=(10, 5))  # ori (4.2, 5.8)

    ax = axs[0]
    df_joints_dataset.boxplot(
        column='mean',
        by='beam_length_bin',
        ax=ax,
        flierprops=flierprops,
        boxprops=boxprops,
        whiskerprops=whiskerprops,
        medianprops=medianprops
        )
    # plt.suptitle('')  # remove the default title
    ax.set_title('(A)')
    ax.set_xlabel('beam length (m)', fontsize=12)
    ax.set_ylabel('error (mm)', fontsize=12, labelpad=labelpad_y)
    ax.grid()

    ax.tick_params(axis='both', which='both', direction='in', top=True, right=True, labelsize=11, pad=pad)
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))

    # plt.tight_layout()
    # plt.show()  # TODO: debug

    # -----------------------------------------------------------------------------------------------
    # Joint position error - distance from beam midpoint 
    # -----------------------------------------------------------------------------------------------
    # if a value is bigger than the beam's length, it means that the joint is not on the beam and we should not consider it
    df_joints_dataset_copy = df_joints_dataset.copy()
    df_joints_dataset_copy = df_joints_dataset_copy[df_joints_dataset_copy['joint_distance_to_beam_midpoint'] < np.mean(err_beam_lengths)]
    # compute 8 bins from biggest to smallest distance to mid point beam
    bins = np.linspace(np.min(
            np.array(df_joints_dataset_copy["joint_distance_to_beam_midpoint"].tolist())),
        np.max(
            np.array(df_joints_dataset_copy["joint_distance_to_beam_midpoint"].tolist())),
        8)
    labels = [f'{bins[i+1]:.1f}' for i in range(len(bins)-1)]
    df_joints_dataset_copy['joint_distance_to_beam_midpoint_bin'] = pd.cut(df_joints_dataset_copy['joint_distance_to_beam_midpoint'], bins=bins, labels=labels)

    # fig, ax = plt.subplots(figsize=(4.2, 5.8))

    ax = axs[1]
    df_joints_dataset_copy.boxplot(
        column='mean',
        by='joint_distance_to_beam_midpoint_bin',
        ax=ax,
        flierprops=flierprops,
        boxprops=boxprops,
        whiskerprops=whiskerprops,
        medianprops=medianprops
        )
    # ax.suptitle('')
    ax.set_title('(B)')
    ax.set_xlabel('distance from mid-beam (m)', fontsize=12)
    ax.set_ylabel('error (mm)', fontsize=12, labelpad=labelpad_y)
    ax.grid()

    ax.tick_params(axis='both', which='both', direction='in', top=True, right=True, labelsize=11, pad=pad)
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))

    # plt.tight_layout()
    # plt.show()  # TODO: debug

    # -----------------------------------------------------------------------------------------------
    # Jointfaces quality - angles
    # -----------------------------------------------------------------------------------------------
    df_jointfaces_dataset_copy = df_jointfaces_dataset.copy()
    df_jointfaces_dataset_copy = df_jointfaces_dataset_copy[df_jointfaces_dataset_copy['jointface_angle'] >= 0]
    bins = np.linspace(30, 90, 8)  # [30, 40, 50, 60, 70, 80, 90]
    labels = [f'{bins[i+1]:.0f}' for i in range(len(bins)-1)]
    df_jointfaces_dataset_copy['jointface_angle_bin'] = pd.cut(df_jointfaces_dataset_copy['jointface_angle'], bins=bins, labels=labels)

    # fig, ax = plt.subplots(figsize=(4.2, 5.8))

    ax = axs[2]
    df_jointfaces_dataset_copy.boxplot(
        column='mean',
        by='jointface_angle_bin',
        ax=ax,
        flierprops=flierprops,
        boxprops=boxprops,
        whiskerprops=whiskerprops,
        medianprops=medianprops
        )
    # ax.suptitle('')
    ax.set_title('(C)')
    ax.set_xlabel('cut angle (°)', fontsize=12)
    ax.set_ylabel('error (mm)', fontsize=12, labelpad=labelpad_y)
    ax.grid()

    ax.tick_params(axis='both', which='both', direction='in', top=True, right=True, labelsize=11, pad=pad)
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))

    # format the x-acis lables to integer
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))

    plt.tight_layout()
    plt.show()

    # # save the figure
    # fig.savefig(os.path.join(output_path, f'joint_analysis_{__time_stamp__}.png'), dpi=300, bbox_inches='tight')

    # -----------------------------------------------------------------------------------------------
    # Drilling holes
    # -----------------------------------------------------------------------------------------------
    # TODO: to be done

    # -----------------------------------------------------------------------------------------------
    # Assembly display
    # -----------------------------------------------------------------------------------------------
    # pcd = o3d.io.read_point_cloud(R"F:\augmented-carpentry\eval\test_data\tower_upper\b_assembly\tower_upper_trm_cloud_clr.ply")
    # points = np.asarray(pcd.points)
    # colors = np.asarray(pcd.colors)
    
    # # Extract x, y, z coordinates
    # x = points[:, 0]
    # y = points[:, 1]
    # z = points[:, 2]

    # # Extract RGB colors
    # r = colors[:, 0]
    # g = colors[:, 1]
    # b = colors[:, 2]

    # # Create a 3D scatter plot
    # fig = plt.figure(figsize=(10, 7))
    # ax = fig.add_subplot(111, projection='3d')

    # # Scatter plot with colors
    # sc = ax.scatter(x, y, z, c=colors, marker='+')

    # # Set labels
    # ax.set_xlabel('X')
    # ax.set_ylabel('Y')
    # ax.set_zlabel('Z')

    # # Set title
    # ax.set_title('3D Point Cloud with Colors')

    # ax.set_box_aspect([1, 1, 1.2])

    # plt.show()


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
    parser.add_argument('--paths', type=str,
                        help="path(s) to the directory containing the results. This should be the root containing the a_beams and b_assembly folders.\n \
                            NB: if you have multiple paths, start with [] and separate them with commas")
    parser.add_argument('--output_path', type=str, default=f'./',
                        help='path to the directory to save the results')

    args = parser.parse_args()

    _paths: typing.List[str] = []
    if args.paths.startswith('[') and args.paths.endswith(']'):
        print("Multiple paths detected")
        _paths_temp = args.paths[1:-1].split(',')
        _paths_temp = [p.strip() for p in _paths_temp]
        for _p in _paths_temp:
            if not _check_dir_sanity(_p):
                sys.exit(1)
            _paths.append(_p)
    else:
        _paths = [args.paths] if _check_dir_sanity(args.paths) else sys.exit(1)

    _output_path: str = args.output_path if _check_dir_sanity(args.output_path) else sys.exit(1)

    main(_paths,
        _output_path)

