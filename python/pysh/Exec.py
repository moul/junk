import subprocess

class Exec():
    def __init__(self):
        pass

    def run(self, args, outsplit = False, env = None):
        try:
            proc = subprocess.Popen(args, stdout = subprocess.PIPE, stderr = subprocess.STDOUT, env = env)
        except Exception, e:
            print 'Command failed: %s : %s' % (args[0], e)
            return ''
        if outsplit:
            return proc.stdout.readlines()
        return proc.stdout.read()


#        r, w, e = popen2.popen3(cmd)
#        print e.readlines()
#        print r.readlines()
#        r.close()
#        e.close()
#        w.close()

#        status = os.system(cmd)
#        exit_value = status >> 8
#        signal_num = status & 127
#        dumped_core = status & 128 and "(core dumped)" or ""
#        print "Program terminated with status %d from signal %d%s\n" % (
#            exit_value, signal_num, dumped_core)
