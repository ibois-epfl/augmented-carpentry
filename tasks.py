# tasks.py
from invoke import task

@task
def ghcomponentize(c):
    path_ghcomponentizer = "./invokes/ghcomponentize/ghcomponentizer.py"
    c.run(f"python {path_ghcomponentizer} --ghio ./invokes/ghcomponentize/ghio ./py/components ./build/gh")

@task
def versionize(c, version):
    path_versionize = "./invokes/versionize.py"
    c.run(f"python {path_versionize} --version {version}")
