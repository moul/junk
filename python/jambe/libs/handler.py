print __file__

import BaseHTTPServer
import jambe

class jambeHTTPHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    __base = BaseHTTPServer.BaseHTTPRequestHandler
    __base_handle = __base.handle
    protocol = "HTTP/1.0"
    rbufsize = 0 # SocketServer.StreamRequestHandler.setup() [...] self.rfile = self.connection.makefile('rb', self.rbufsize) [...]

    def __init__(self, request, client_address, server):
        #BaseHTTPServer.BaseHTTPRequestHandler.__init__(self, request, client_address, server)
        self._jambe = server._jambe
        self.server_version = self._jambe.version()

        """Content of BaseHTTPServer.BaseHTTPRequestHandler.__init__()"""
        self.request = request
        self.client_address = client_address
        self.server = server
        self.setup()
        try:
            self.handle()
        finally:
            self.finish()
        self._jambe.Mh.invoke_all('HTTPHandler_init', handler)

    def send(self, content = '', code = 200, message = 'OK', headers = {}):
        if not 'Content-Type' in headers:
            headers['Content-Type'] = 'text/html; charset=utf-8'

        #headers['Expires'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
        #headers['Last-Modified'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
        #headers['Cache-Control'] = 'must-revalidate'
        #headers['X-Powered-By'] = 'jambe'

        headers['Content-Length'] = len(content)
        if 'gzip' in self.headers.get('Accept-Encoding', 'none').split(','):
            from StringIO import StringIO
            import gzip
            headers['Content-Encoding'] = 'gzip'
            f = StringIO()
            gzf = gzip.GzipFile(mode = "wb", fileobj = f, compresslevel = 1)
            gzf.write(content)
            gzf.close()
            content  = f.getvalue()
            f.close()
            new_content_length = len(content)
            self.log_message('Gzip: old-length=%s, new-length=%s' % (headers['Content-Length'], new_content_length))
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

    def handle(self):
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
