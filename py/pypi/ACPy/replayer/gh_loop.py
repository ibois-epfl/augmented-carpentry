import sys
from inspect import currentframe
import scriptcontext as sc
import Grasshopper as gh

class GHLoop:
    def __init__(self, items):
        
        self.items = items

        current_frame = currentframe()
        caller_frame = current_frame.f_back
        caller_ghenv = caller_frame.f_locals['ghenv']

        self.ghenv = caller_ghenv
        
        self.guid = str(self.ghenv.Component.get_InstanceGuid())

    def callback(self, e):
        self.ghenv.Component.ExpireSolution(False)

    def get_next(self):
        STATUS_WIP = "WIP" + self.guid
        LOOP_INDEX = "LOOP_INDEX" + self.guid

        if STATUS_WIP not in sc.sticky:
            sc.sticky[STATUS_WIP] = STATUS_WIP
            sc.sticky[LOOP_INDEX] = 0
        
        idx = sc.sticky[LOOP_INDEX]
        sc.sticky[LOOP_INDEX] += 1
        if sc.sticky[LOOP_INDEX] == len(self.items):
            self.ghenv.Component.Message = ""
            sc.sticky.pop(STATUS_WIP)
        else:
            self.ghenv.Component.Message = str(int(sc.sticky[LOOP_INDEX]/len(self.items) * 100)) + "%"
            self.ghenv.Component.OnPingDocument() \
                .ScheduleSolution(1, gh.Kernel.GH_Document.GH_ScheduleDelegate(self.callback))

        return idx, self.items[idx]

# sys.modules["GHLoop"] = GHLoop
