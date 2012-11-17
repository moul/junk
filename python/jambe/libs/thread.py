print __file__

import BaseHTTPServer
import SocketServer
import threading
import select

class ThreadingHTTPServer(SocketServer.ThreadingMixIn, BaseHTTPServer.HTTPServer):
    def __init__(self, jambe, handler_class, server_address = None):
        BaseHTTPServer.HTTPServer.__init__(self, server_address, handler_class)
        self._jambe = jambe

    def run(self):
        run_event = threading.Event()
        req_count = 0
        while not run_event.isSet():
            try:
                self.handle_request()
                req_count += 1
                if req_count == 10:
                    self._jambe.Log.log("Number of active threads: %s" % threading.activeCount())
                    req_count = 0
            except select.error, e:
                if e[0] == 4 and run_event.isSet():
                    pass
                else:
                    self._jambe.Log.log("Errno: %d - %s" % (e[0], e[1]))
        self._jambe.Log.log("Server shutdown")

def exitHandler(signo, frame):
    from types import FrameType, CodeType
    while frame and isinstance(frame, FrameType):
        if frame.f_code and isinstance(frame.f_code, CodeType):
            if "run_event" in frame.f_code.co_varnames:
                frame.f_locals["run_event"].set()
                return
        frame = frame.f_back

def setup(jambe, handler_class, server_address = None):
    from signal import signal, SIGINT
    signal(SIGINT, exitHandler)

    return ThreadingHTTPServer(jambe, handler_class, server_address)
