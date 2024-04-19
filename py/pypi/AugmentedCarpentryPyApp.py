#! python3
""" Tester python for the pypi module """


import Rhino
import Rhino.Geometry as rg

TOL_DOC = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance
ACTIV_DOC = Rhino.RhinoDoc.ActiveDoc

import AugmentedCarpentryPy as acpy

if __name__ == "__main__":
    print(f"Version pacakge: {acpy.__version__}")

    print("Hello from the pypi module!")
    print("Tolerance: ", TOL_DOC)
    print("Active Doc: ", ACTIV_DOC)
    print("Rhino.Geometry: ", rg)
    print("Rhino: ", Rhino)