print __file__

DEFAULT_SERVER_ADDRESS = '127.0.0.1'
DEFAULT_SERVER_PORT = 8000

import jambe

class jambeProxy(jambe.Jambe):
    def __init__(self):
        jambe.Jambe.__init__(self)

    def _bootstrap_proxy(self):
        import jambe.libs.thread
        import jambe.libs.handler_http
        jambe.libs.handler_http.jambeHandlerHTTP.__version__ = self.version()
        server_address = self.variable_get('server_address', DEFAULT_SERVER_ADDRESS)
        server_port = self.variable_get('server_port', DEFAULT_SERVER_PORT)
        import socket
        try:
            self.Proxy = jambe.libs.thread.setup(self, jambe.libs.handler_http.jambeHandlerHTTP, (server_address, server_port))
        except socket.error, e:
            raise self.Exception("Socket error: %s" % e)
        print "Servering on %s port %d" % self.Proxy.socket.getsockname()
        print "[+] proxy"

    def routine(self):
        import jambe.libs.thread
        self.Proxy.run()
        pass

def main():
    from optparse import OptionParser
    parser = OptionParser(usage = '%prog [allowed-ip [allowed-ip-2 [...]]]')
    parser.add_option('-p', '--port', dest = 'server_port', action = 'store', help = 'Port to bind to', default = False, type = 'int')
    parser.add_option('-f', '--logfile', dest = 'logfile', action = 'store', help = 'Path to logfile. If not specified, STDOUT is used', default = None)
    parser.add_option('-d', '--daemon', dest = 'daemon', action = 'store_true', help = 'Run in the background', default = False)
    parser.add_option('-m', '--max-log-size', dest = 'max_log_size', action = 'store', default = 20, type = 'int')
    parser.add_option('-c', '--config', dest = 'config_name', action = 'store', default = False)
    parser.add_option('-l', '--log-level', dest = 'log_level', action = 'store', default = 20, type = 'int', help = 'no: 0, debug: 10, info: 20, warn: 30, error: 40, critical: 50')
    parser.add_option('-s', '--server-address', dest = 'server_address', action = 'store', default = None)

    (options, args) = parser.parse_args()

    jambe = jambeProxy()

    jambe.variable_set_multiple(options.__dict__)
    if args:
        jambe.variable_set('allowed_ips', args)
    jambe.variable_set('enabled_modules', ['core', 'proxy_http', 'admin', 'user', 'session'])
    try:
        jambe.bootstrap(jambe.BOOT_FULL)
        jambe._bootstrap_proxy()
    except jambe.Exception, e:
        print "[-] %s" % e
        return 1
    ret = jambe.routine()
    import sys
    sys.exit(ret)
