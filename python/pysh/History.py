import os
import atexit
import readline

class History():
    def __init__(self, history_file = os.path.join(os.environ["HOME"], ".pysh_history")):
        self.history_file = history_file
        try:
            readline.read_history_file(self.history_file)
        except IOError:
            pass
        atexit.register(readline.write_history_file, self.history_file)


