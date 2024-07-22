from inspect import currentframe
import scriptcontext as sc
import Grasshopper as gh

class GHLoop:
    def __init__(self, items, ghenv=None):
        self.items = items

        # retrive the ghenv from the caller component
        if ghenv is None:
            current_frame = currentframe()
            caller_frame = current_frame.f_back
            caller_ghenv = caller_frame.f_locals['ghenv']
            self.ghenv = caller_ghenv
        else:
            self.ghenv = ghenv
            
        self.guid = str(self.ghenv.Component.get_InstanceGuid())

        # key for sticky dictionary
        self.STATUS_WIP = "WIP" + self.guid
        self.LOOP_INDEX = "self.LOOP_INDEX" + self.guid
    
    def __len__(self):
        return len(self.items)

    def _callback(self, e):
        self.ghenv.Component.ExpireSolution(False)

    def reset(self):
        if self.STATUS_WIP in sc.sticky:
            sc.sticky.pop(self.STATUS_WIP)
        if self.LOOP_INDEX in sc.sticky:
            sc.sticky.pop(self.LOOP_INDEX)

    def get_next(self):
        if self.STATUS_WIP not in sc.sticky:
            sc.sticky[self.STATUS_WIP] = self.STATUS_WIP
            sc.sticky[self.LOOP_INDEX] = 0
        
        idx = sc.sticky[self.LOOP_INDEX]
        sc.sticky[self.LOOP_INDEX] += 1
        if sc.sticky[self.LOOP_INDEX] == len(self.items):
            self.ghenv.Component.Message = ""
            sc.sticky.pop(self.STATUS_WIP)
        else:
            self.ghenv.Component.Message = str(int(sc.sticky[self.LOOP_INDEX]/len(self.items) * 100)) + "%"
            self.ghenv.Component.OnPingDocument() \
                .ScheduleSolution(1, gh.Kernel.GH_Document.GH_ScheduleDelegate(self._callback))

        return idx, self.items[idx]

# import sys
# sys.modules["GHLoop"] = None
# sys.modules["GHLoop"] = GHLoop
