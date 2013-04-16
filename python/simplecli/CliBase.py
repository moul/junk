import readline
import shlex

class CliBase:
    def __init__(self):
        print 'init'

    def run(self):
        while True:
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
