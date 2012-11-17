try:
        import readline
        import rlcompleter
except ImportError:
        print "Module readline not available."
else:
        readline.parse_and_bind('bind ^I rl_complete')
        readline.parse_and_bind("tab: complete")

import os

class Completer(rlcompleter.Completer):
    def __init__(self, tab='    '):
        self.tab = tab
        rlcompleter.Completer.__init__(self)
        self.binaries_in_paths = []
        for dirname in os.getenv('PATH').split(':'):
            for dirname, dirnames, filenames in os.walk(dirname):
                for filename in filenames:
                    if not filename in self.binaries_in_paths:
                        self.binaries_in_paths.append(filename)
        self.binaries_in_paths = sorted(self.binaries_in_paths)

    def complete(self, text, state):
        if text == '':
            return None
        else:
            opts = [x for x in self.binaries_in_paths if x.startswith(text)]
            try:
                return opts[state]
            except IndexError:
                return None
            #return rlcompleter.Completer.complete(self,text,state)
