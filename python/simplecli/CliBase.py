class CliBase:
    def __init__(self):
        print 'init'

    def run(self):
        while True:
            cmd = raw_input('prompt> ')
            parts = cmd.split(' ')
            if hasattr(self, 'cmd_%s' % parts[0]):
                method = getattr(self, 'cmd_%s' % parts[0])
                method(*parts[1:])
            else:
                print 'command not found'
