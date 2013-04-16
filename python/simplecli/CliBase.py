import readline
import shlex
import os
import sys
import atexit

class CliBase:
    def __init__(self, histfile = '~/simplecli.history'):
        histfile = os.path.expanduser(histfile)
        try:
            readline.read_history_file(histfile)
        except:
            pass
        atexit.register(readline.write_history_file, histfile)

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
                sys.exit(0)
