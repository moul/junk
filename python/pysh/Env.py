import os

class Env():
    def __init__(self, map = os.environ):
        self.map = map
        pass

    def export(self):
        return self.map
