#! python3

import os
import sys
import argparse
import shutil
import typing

def main(
    gh_components_dir: str,
    build_dir: str,
    manifest_path: str,
    logo_path: str,
    readme_path: str,
    license_path: str,
) -> bool:
    current_file_path = os.path.abspath(__file__)
    current_directory = os.path.dirname(current_file_path)

    #####################################################################
    # Copy manifest, logo, misc folder (readme, license, etc)
    #####################################################################
    shutil.copy(manifest_path, build_dir)
    shutil.copy(logo_path, build_dir)
    path_miscdir : str = os.path.join(build_dir, "misc")
    os.makedirs(path_miscdir, exist_ok=False)
    shutil.copy(readme_path, path_miscdir)
    shutil.copy(license_path, path_miscdir)

    for f in os.listdir(gh_components_dir):
        if f.endswith(".ghuser"):
            shutil.copy(os.path.join(gh_components_dir, f), build_dir)

    #####################################################################
    # Yak exe
    #####################################################################
    yak_exe_path : str = os.path.join(current_directory, "exec", "Yak.exe")
    yak_exe_path = os.path.abspath(yak_exe_path)

    path_current : str = os.getcwd()
    os.chdir(build_dir)
    os.system("cd")
    try:
        os.system(f"{yak_exe_path} build")
    except Exception as e:
        print(f"Failed to build the yak package: {e}")
        return False
    os.chdir(path_current)

    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="The invoke task to yakerize the ghcomponents into a yak package."
    )
    parser.add_argument(
        "--gh-components-dir",
        type=str,
        required=True,
        help="The path to the ghcomponents directory."
    )
    parser.add_argument(
        "--build-dir",
        type=str,
        required=True,
        default="./build/yak",
        help="The path where the yak will be built."
    )
    parser.add_argument(
        "--manifest-path",
        type=str,
        required=False,
        default="./manifest.yml",
        help="The path to the manifest file."
    )
    parser.add_argument(
        "--logo-path",
        type=str,
        required=False,
        default="./logo.png",
        help="The path to the logo file."
    )
    parser.add_argument(
        "--license-path",
        type=str,
        required=False,
        default="./LICENSE",
        help="The path to the license file."
    )
    parser.add_argument(
        "--readme-path",
        type=str,
        required=False,
        default="./README.md",
        help="The path to the readme file."
    )

    args = parser.parse_args()
    parse_errors = []

    is_gh_components_dir_correct = True
    if not os.path.isdir(args.gh_components_dir):
        parse_errors.append(f"Path to ghcomponents directory is invalid: {args.gh_components_dir}")
        is_gh_components_dir_correct = False
    if not any([f.endswith(".ghuser") for f in os.listdir(args.gh_components_dir)]):
        parse_errors.append(f"No .ghuser files found in the ghcomponents directory: {args.gh_components_dir}")
        is_gh_components_dir_correct = False
    for f in os.listdir(args.gh_components_dir):
        if not f.endswith(".ghuser"):
            parse_errors.append(f"Found non .ghuser file in the ghcomponents directory: {f}")
            is_gh_components_dir_correct = False

    is_build_dir_correct = True
    if os.path.isdir(args.build_dir):
        for f in os.listdir(args.build_dir):
            file_path = os.path.join(args.build_dir, f)
            try:
                if os.path.isfile(file_path) or os.path.islink(file_path):
                    os.unlink(file_path)
                elif os.path.isdir(file_path):
                    shutil.rmtree(file_path)
            except Exception as e:
                print(f"Failed to delete {file_path}: {e}")
                is_build_dir_correct = False
    else:
        os.makedirs(args.build_dir, exist_ok=False)
    if not os.path.isdir(args.build_dir):
        parse_errors.append(f"Path to build directory is invalid: {args.build_dir}")
        is_build_dir_correct = False

    is_manifest_path_correct = True
    if not os.path.isfile(args.manifest_path):
        parse_errors.append(f"Path to manifest file is invalid: {args.manifest_path}")
        is_manifest_path_correct = False

    is_logo_path_correct = True
    if not os.path.isfile(args.logo_path):
        parse_errors.append(f"Path to logo file is invalid: {args.logo_path}")
        is_logo_path_correct = False

    is_license_path_correct = True
    if not os.path.isfile(args.license_path):
        parse_errors.append(f"Path to license file is invalid: {args.license_path}")
        is_license_path_correct = False

    is_readme_path_correct = True
    if not os.path.isfile(args.readme_path):
        parse_errors.append(f"Path to readme file is invalid: {args.readme_path}")
        is_readme_path_correct = False

    print("Yakerize check:")
    print(f"\t[{'x' if is_gh_components_dir_correct else ' '}] Ghcomponents directory: {args.gh_components_dir}")
    print(f"\t[{'x' if is_build_dir_correct else ' '}] Build directory: {args.build_dir}")
    print(f"\t[{'x' if is_manifest_path_correct else ' '}] Manifest file path: {args.manifest_path}")
    print(f"\t[{'x' if is_logo_path_correct else ' '}] Logo file path: {args.logo_path}")
    print(f"\t[{'x' if is_license_path_correct else ' '}] License file path: {args.license_path}")
    print(f"\t[{'x' if is_readme_path_correct else ' '}] Readme file path: {args.readme_path}")
    if parse_errors:
        for error in parse_errors:
            print(error)
        sys.exit(1)
    print("Starting the yakerize task...")

    res = main(
        gh_components_dir=args.gh_components_dir,
        build_dir=args.build_dir,
        manifest_path=args.manifest_path,
        logo_path=args.logo_path,
        readme_path=args.readme_path,
        license_path=args.license_path
    )
    if res:
        print("[x] Yakerize task completed.")
    else:
        print("[ ] Yakerize task failed.")
        sys.exit(1)