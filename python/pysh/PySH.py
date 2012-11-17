import os
import sys
import popen2
from libpysh import Completer, Prompt, Exec, Builtins, Env, Parser, History

class PySH():
    def __init__(self):
        self.Readline = Completer.Completer()
        self.Prompt = Prompt.Prompt()
        self.Exec = Exec.Exec()
        self.Builtins = Builtins.Builtins()
        self.Env = Env.Env()
        self.Parser = Parser.Parser()
        self.History = History.History()

    def read(self):
        return raw_input(self.Prompt)

    def execute(self, cmd_args):
        print self.Exec.run(cmd_args, env = self.Env.export())
