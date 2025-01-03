#! python3 

import os
import sys
import argparse
import re

import typing


def main(
    version: str,
    path_manifest: str,
    path_setup: str,
    path_init: str,
    is_from_manifest: bool,
    *args, **kwargs
) -> bool:
    # modify the manifest file
    if not is_from_manifest:
        manifest_crt_version = None
        with open(path_manifest, "r") as f:
            manifest = f.read()
            match = re.search(r"version: (\d+\.\d+\.\d+)", manifest)
            if match:
                manifest_crt_version = match.group(1)
        if manifest_crt_version is not None:
            if version <= manifest_crt_version:
                print(f"Version {version} is equal or smaller than the current version {manifest_crt_version}. Please provide a version number bigger than the current one.")
                return
        else:
            print("Could not find the current version in the manifest file.")
            sys.exit(1)
        with open(path_manifest, "r") as f:
            manifest = f.read()
        manifest = re.sub(r"version: \d+\.\d+\.\d+", f"version: {version}", manifest)
        with open(path_manifest, "w") as f:
            f.write(manifest)

    # modify the setup file
    setup_crt_version = None
    with open(path_setup, "r") as f:
        setup = f.read()
        match = re.search(r"version=\"(\d+\.\d+\.\d+)\"", setup)
        if match:
            setup_crt_version = match.group(1)
    if setup_crt_version is not None:
        if version <= setup_crt_version:
            print(f"Version {version} is equal or smaller than the current version {setup_crt_version}. Please provide a version number bigger than the current one.")
            return False
    else:
        print("Could not find the current version in the setup file.")
        sys.exit(1)
    with open(path_setup, "r") as f:
        setup = f.read()
    setup = re.sub(r"version=\"\d+\.\d+\.\d+\"", f"version=\"{version}\"", setup)
    with open(path_setup, "w") as f:
        f.write(setup)

    # modify the __init__ file
    init_crt_version = None
    with open(path_init, "r") as f:
        init = f.read()
        match = re.search(r"__version__ = \"(\d+\.\d+\.\d+)\"", init)
        if match:
            init_crt_version = match.group(1)
    if init_crt_version is not None:
        if version <= init_crt_version:
            print(f"Version {version} is equal or smaller than the current version {init_crt_version}. Please provide a version number bigger than the current one.")
            return False
    else:
        print("Could not find the current version in the __init__ file.")
        sys.exit(1)
    with open(path_init, "r") as f:
        init = f.read()
    init = re.sub(r"__version__ = \"\d+\.\d+\.\d+\"", f"__version__ = \"{version}\"", init)
    with open(path_init, "w") as f:
        f.write(init)

    return True

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Update the version number everywhere in code base."
    )
    parser.add_argument(
        "--from-manifest",
        action='store_true',
        default=False,
        help="Whether to update the version from the manifest file's version."
    )
    parser.add_argument(
        "--version",
        type=str,
        required=False,
        help="The version number to update and overwrite in the code base."
    )
    parser.add_argument(
        "--path-manifest",
        type=str,
        required=False,
        default="./manifest.yml",
        help="The path to the manifest file."
    )
    parser.add_argument(
        "--path-setup",
        type=str,
        required=False,
        default="./py/pypi/setup.py",
        help="The path to the setup file."
    )
    parser.add_argument(
        "--path-init",
        type=str,
        required=False,
        default="./py/pypi/ACPy/__init__.py",
        help="The path to the __init__ file."
    )

    args = parser.parse_args()
    parse_errors = []

    _manifest_version = None
    if args.from_manifest:
        if not os.path.isfile(args.path_manifest):
            parse_errors.append(f"Path to manifest file is invalid: {args.path_manifest}")
        with open(args.path_manifest, "r") as f:
            manifest = f.read()
            match = re.search(r"version: (\d+\.\d+\.\d+)", manifest)
            if match:
                _manifest_version = match.group(1)
        if _manifest_version is None:
            parse_errors.append("Could not find the version number in the manifest file.")
        args.version = _manifest_version

    is_version_ok = True
    _version = args.version
    if not re.match(r"^\d+\.\d+\.\d+$", _version) \
        or _version.count(".") < 2 \
        or len(_version) < 5:
        is_version_ok = False
        parse_errors.append("Version must be in the format: Major.Minor.Patch")
        
    is_manifest_ok = True
    is_setup_ok = True
    is_init_ok = True
    if not os.path.isfile(args.path_manifest):
        is_manifest_ok = False
        parse_errors.append(f"Path to manifest file is invalid: {args.path_manifest}")
    if not os.path.isfile(args.path_setup):
        is_setup_ok = False
        parse_errors.append(f"Path to setup file is invalid: {args.path_setup}")
    if not os.path.isfile(args.path_init):
        is_init_ok = False
        parse_errors.append(f"Path to __init__ file is invalid: {args.path_init}")

    print("Versionizer checks:")
    if is_version_ok:
        print("\t[x] Correct version format")
    else:
        print(f"\t[ ] Correct version format")
    if is_manifest_ok:
        print("\t[x] Manifest file path is valid")
    else:
        print(f"\t[ ] Manifest file path is valid")
    if is_setup_ok:
        print("\t[x] Setup file path is valid")
    else:
        print(f"\t[ ] Setup file path is valid")
    if is_init_ok:
        print("\t[x] __init__ file path is valid")
    else:
        print(f"\t[ ] __init__ file path is valid")
    if parse_errors.__len__() != 0:
        print("[ERRORS]:")
        for error in parse_errors:
            print(f"\t-{error}")
    else:
        print("Starting versionizer...")

    res = main(
        version=_version,
        path_manifest=args.path_manifest,
        path_setup=args.path_setup,
        path_init=args.path_init,
        is_from_manifest=args.from_manifest
    )

    if res:
        print("[x] Versionizer completed successfully.")
    else:
        print("[ ] Versionizer failed.")
        sys.exit(1)