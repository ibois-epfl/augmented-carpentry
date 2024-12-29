"""
    This main.py file is used to define all the macros
    for the Python scripts in the docs/scripts directory
    to be called in the mkdocs markdown files.
"""

import subprocess

def define_env(env):
    @env.macro
    def run_python_script(script_path):
        result = subprocess.run(['python', script_path], capture_output=True, text=True)
        return result.stdout