# tasks.py
from invoke import task

@task
def ghcomponentize(c):
    path_ghcomponentizer = "./invokes/ghcomponentizer.py"
    c.run(f"python {path_ghcomponentizer} --ghio ./yaker/ghio ./py/components ./build/gh")