# tasks.py
from invoke import task

@task
def ghcomponentize(c):
    path_ghcomponentizer = "./invokes/ghcomponentize/ghcomponentizer.py"
    c.run(f"python {path_ghcomponentizer} --ghio ./invokes/ghcomponentize/ghio ./py/components ./build/gh")

@task
def versionize(c):
    path_versionize = "./invokes/versionize.py"
    c.run(f"python {path_versionize} --from-manifest")

@task
def flagerize(c, package_name="ACPy"):
    path_flagerize = "./invokes/flagerize.py"
    c.run(f"python {path_flagerize} --package {package_name} --from-manifest")