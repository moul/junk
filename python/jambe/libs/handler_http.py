print __file__

import BaseHTTPServer
import jambe

class jambeHandlerHTTP(BaseHTTPServer.BaseHTTPRequestHandler):
    __base = BaseHTTPServer.BaseHTTPRequestHandler
    __base_handle = __base.handle
    protocol = "HTTP/1.0"
    rbufsize = 0 # SocketServer.StreamRequestHandler.setup() [...] self.rfile = self.connection.makefile('rb', self.rbufsize) [...]

    def __init__(self, request, client_address, server):
        #BaseHTTPServer.BaseHTTPRequestHandler.__init__(self, request, client_address, server)
        self._jambe = server._jambe
        self._jambe._bootstrap_db(check_install = False, reload = True)
        self.server_version = self._jambe.version()
        self._jambe.Mh.invoke_all('HandlerHTTP_init', self)

        """Content of BaseHTTPServer.BaseHTTPRequestHandler.__init__()"""
        self.request = request
        self.client_address = client_address
        self.server = server
        self.setup()
        try:
            self.handle()
        finally:
            self.finish()
        """End of Content"""
        import SocketServer
        SocketServer.BaseServer.handle_error = self.handle_error

    def send(self, content = '', code = 200, message = 'OK', headers = {}):
        if not 'Content-Type' in headers:
            headers['Content-Type'] = 'text/html; charset=utf-8'

        #headers['Expires'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
        #headers['Last-Modified'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
        #headers['Cache-Control'] = 'must-revalidate'
        #headers['X-Powered-By'] = 'jambe'

        headers['Content-Length'] = len(content)
        if 'gzip' in self.headers.get('Accept-Encoding', 'none').split(','):
            import StringIO
            import gzip
            headers['Content-Encoding'] = 'gzip'
            f = StringIO.StringIO()
            gzf = gzip.GzipFile(mode = "wb", fileobj = f, compresslevel = 1)
            gzf.write(content)
            gzf.close()
            content  = f.getvalue()
            f.close()
            new_content_length = len(content)
            self._jambe.Log.log('Gzip: old-length=%s, new-length=%s' % (headers['Content-Length'], new_content_length))
            headers['Content-Length'] = new_content_length

        self.send_response(code, message)
        for key in headers:
            self.send_header(key, headers[key])
        self.end_headers()

        if self.command != 'HEAD' and code >= 200 and code not in (204, 304):
            self.wfile.write(content)

    def send_error(self, code, message = None):
        import jambe.libs.theme
        """ Override BaseHTTPServer.send_error() """
        try:
            short, long = self.responses[code]
        except KeyError:
            short, long = '???', '???'
        if message is None:
            message = short
        explain = long
        self.log_error("code %d, message %s", code, message)
        # using _quote_html to prevent Cross Site Scripting attacks (see bug #1100201)
        content = self._jambe.Theme.render_template('error.html', {'code': code, 'message': BaseHTTPServer._quote_html(message), 'explain': explain})
        headers = {'Content-Type': self.error_content_type,
                   'Connection': 'close'}
        self.send(content = content, headers = headers, code = code, message = message)

#    def handle(self):
#        self.close_connection = 1
#        self.handle_one_request()

    def handle_one_request(self):
        """ override """
        import socket
        try:
            self.raw_requestline = self.rfile.readline()
            #self._jambe.Log.log("test %s" % self.raw_requestline)
            if not self.raw_requestline:
                self.close_connection = 1
                return
            if not self.parse_request():
                self._jambe.Log.log('parse_request unsuccessfull', type = self._jambe.Log.LOG_ERROR)
                # An error code has been sent, just exit
                return
            import urlparse
            self._url = urlparse.urlparse(self.path, 'http')
            #self._jambe.Log.log("blibli %s" % self.command)
            mname = 'HandlerHTTP_method_' + self.command
            if not self._jambe.Mh.invokable('hook_%s' % mname):
            #if not hasattr(self, mname):
                self.send_error(501, "Unsupported method (%r)" % self.command)
                return
            #method = getattr(self, mname)
            #method()
            self._jambe.Mh.invoke_all(mname, self)
            self.wfile.flush() #actually send the response if not already done.
        except socket.timeout, e:
            #a read or a write timed out.  Discard this connection
            self.log_error("Request timed out: %r", e)
            self.close_connection = 1
            return

    def handle_error(self, request, client_address):
        import StringIO
        """Override"""
        self._jambe.Log.log('-' * 40)
        self._jambe.Log.log('*** Exception happened during processing of request from')
        self._jambe.Log.log(client_address)
        import traceback
        file = StringIO.StringIO()
        traceback.print_exc(file = file) # XXX But this goes to stderr!
        self._jambe.Log.log(file.getvalue())
        self._jambe.Log.log('-' * 40)


    def DEPRECATED_handle(self):
#self.timer_start = datetime.datetime.today()
        (ip, port) =  self.client_address
        self._jambe.Log.log("Request from '%s'" % ip)
        if hasattr(self, 'allowed_clients') and ip not in self.allowed_clients:
            self.raw_requestline = self.rfile.readline()
            if self.parse_request():
                self._jambe['requests']['not allowed by ip'] += 1
                self.send_error(403)
        else:
            self.__base_handle()

    def _connect_to(self, netloc, soc):
        i = netloc.find(':')
        if i >= 0:
            host_port = netloc[:i], int(netloc[i + 1:])
        else:
            host_port = netloc, 80
        self._jambe.Log.log("connect to %s:%d" % (host_port[0], host_port[1]))
        import socket
        try:
            soc.connect(host_port)
        except socket.error, arg:
            try:
                msg = arg[1]
            except:
                msg = arg
            self.send_error(500, msg)
            return 0
        return 1

    def _read_write(self, soc, max_idling = 20, local = False):
        import select
        import socket
        iw = [self.connection, soc]
        local_data = ""
        ow = []
        count = 0
        stats_read = 0
        stats_write = 0
        while 1:
#            if self.connection._sock.__class__ == socket._closedsocket:
#                return None
            count += 1
            (ins, _, exs) = select.select(iw, ow, iw, 1)
            if exs:
                break
            if ins:
                for i in ins:
                    if i is soc:
                        out = self.connection
                    else:
                        out = soc
                    data = i.recv(8192)
                    stats_read += len(data)
                    if data:
                        if local:
                            local_data += data
                        else:
                            stats_write += len(data)
                            out.send(data)
                        count = 0
            if count == max_idling:
                break
        if local:
            return local_data
        return stats_read, stats_write
        return None

def setup(jambe):
    return jambeHandlerHTTP(jambe)
