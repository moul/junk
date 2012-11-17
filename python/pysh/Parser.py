from shlex import shlex

class Parser():
    def __init__(self):
        pass

    def parse(self, cmd_str):
#        cmd_args = cmd_str.split()
        lexer = shlex(cmd_str, posix = True)
        lexer.whitespace_split = True
        cmd_args = [token for token in lexer]
        print cmd_args
        return cmd_args
