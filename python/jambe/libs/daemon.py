print __file__

def setup(daemon = True, logger = None):
    import os
    import sys
    from time import sleep
    class DevNull(object):
        def __init__(self):
            self.fd = os.open("/dev/null", os.O_WRONLY)
        def write(self, *args, **kwargs):
            return 0
        def read(self, *args, **kwargs):
            return 0
        def fileno(self):
            return self.fd
        def close(self):
            os.close(self.fd)
    class ErrorLog:
        def __init__(self, obj):
            self.obj = obj
        def write(self, string):
            self.obj.log(logging.ERROR, string)
        def read(self, *args, **kwargs):
            return 0
        def close(self):
            pass
    if os.fork() != 0:
        ## allow the child pid to instanciate the server class
        sleep(1)
        sys.exit(0)
    os.setsid()
    fd = os.open('/dev/null', os.O_RDONLY)
    if fd != 0:
        os.dup2(fd, 0)
        os.close(fd)
    null = DevNull()
    if logger:
        log = ErrorLog(logger)
        sys.stderr = log
    else:
        sys.stderr = null
    sys.stdout = null
    sys.stdin = null
    fd = os.open('/dev/null', os.O_WRONLY)
    #if fd != 1:                                                                                                                                     
    #    os.dup2(fd, 1)                                                                                                                              
    os.dup2(sys.stdout.fileno(), 1)
    if fd != 2:
        os.dup2(fd, 2)
    if fd not in(1, 2):
        os.close(fd)
