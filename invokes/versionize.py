#! python3 

import os
import sys
import argparse
import re

import typing


def main(
    version: str
) -> None:
    pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Update the version number everywhere in code base."
    )
    parser.add_argument(
        "--version",
        type=str,
        help="The version number to update and overwrite in the code base."
    )
    parser.add_argument(
        "--path-manifest",
        type=str,
        help="The path to the manifest file."
    )
    args = parser.parse_args()

    parse_errors = []

    is_version_ok = True
    _version = args.version
    if not re.match(r"^\d+\.\d+\.\d+$", _version) \
        or _version.count(".") < 2 \
        or len(_version) < 5:
        is_version_ok = False
    else:
        parse_errors.append("Version must be in the format: Major.Minor.Patch")
    
    print("Versionizer checks:")
    if is_version_ok:
        print("\t[x] Correct version format")
    else:
        print(f"\t[ ] Correct version format")
    
    if parse_errors.__len__() != 0:
        print("[ERRORS]:")
        for error in parse_errors:
            print(f"\t-{error}")


    main(version=_version)