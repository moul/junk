import readline
import shlex
from sys import exit

class CliBase:
    def __init__(self):
        print 'init'

    def run(self):
        while True:
            try:
                raw = raw_input('prompt> ')
                shl = shlex.shlex(raw)
                shl.wordchars += '.-/:,='
                shl.escapedquotes = '"\''
                parts = list(shl)
                if hasattr(self, 'cmd_%s' % parts[0]):
                    method = getattr(self, 'cmd_%s' % parts[0])
                    method(*parts[1:])
                else:
                    print 'command not found'
            except (KeyboardInterrupt,):
                print
            except (SystemExit):
                print 'exit'
            except (EOFError):
                print 'exit'
                exit(0)
