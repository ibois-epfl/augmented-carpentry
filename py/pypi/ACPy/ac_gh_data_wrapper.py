class GHDataWrapper:
    """
    This class is a wrapper for exchanging data between Grasshopper components.
    Since Grasshopper components are not able to pass dictionaries, this class
    is used to wrap the data in a class instance.
    """
    
    def __init__(self, data):
        self.data = data
    
    def retrive_data(self):
        return self.data