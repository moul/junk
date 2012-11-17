print __file__

import jambe.libs.modules

class ProxyHTTP(jambe.libs.modules.jambeModule):
    _dependencies = ['user', 'core']

    def __init__(self, _jambe):
        jambe.libs.modules.jambeModule.__init__(self, _jambe)
        self.hook_HandlerHTTP_method_PUT = self.hook_HandlerHTTP_method_GET
        self.hook_HandlerHTTP_method_POST = self.hook_HandlerHTTP_method_GET
        self.hook_HandlerHTTP_method_HEAD = self.hook_HandlerHTTP_method_GET

    def hook_HandlerHTTP_init(self, handler):
        #self._handler = handler
        #handler.do_GET = self.do_GET
        #handler.do_HEAD = self.do_GET
        #handler.do_PUT = self.do_GET
        #handler.do_POST = self.do_GET
        pass

    def hook_HandlerHTTP_method_CONNECT(self, handler):
        #handler.send_error(400, "do_CONNECT TODO :)")
        #return

        import socket
        self._jambe.Log.log("%s %s" % (handler.address_string(), 'do_CONNECT TODO'))
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            if handler._connect_to(handler.path, soc):
                #self.log_request(200)
                handler.wfile.write(handler.protocol_version + " 200 Connection established\r\n")
                handler.wfile.write("Proxy-agent: %s\r\n" % handler.version_string())
                handler.wfile.write("\r\n")
                handler._read_write(soc, 300)
        finally:
            soc.close()
            handler.connection.close()

    def _proxying_http(self, handler):
        import socket
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #soc.setblocking(0)
        try:
            if handler._connect_to(handler._url.netloc, soc):
                #self.log_request()
                import urlparse
                (newpath,) = urlparse.urlunparse(('', '', handler._url.path, handler._url.params, handler._url.query, '')),
                soc.send("%s %s %s\r\n" %(handler.command, newpath, handler.request_version))
                handler.headers['Connection'] = 'close'
                del handler.headers['Proxy-Connection']
                del handler.headers['proxy-authorization']
                #del handler.headers['If-None-Match']
                #del handler.headers['If-Modified-Since']
                #for key in handler.headers:
                for key_val in handler.headers.items():
                    #self._handler.send_header(key, self._handler.headers[key])
                    soc.send("%s: %s\r\n" % key_val)
                    #self._handler.end_header()
                soc.send("\r\n")
                if soc._sock and handler.connection._sock:
                    (read, write) = handler._read_write(soc)
                    self._jambe.Log.log('Read: %s, Write: %s' % (read, write))
        finally:
            soc.close()
            handler.connection.close()

    def _proxying_ftp(self, handler):
        raise notImplementedError
        # fish out user and password information
        i = netloc.find('@')
        if i >= 0:
            login_info, netloc = netloc[:i], netloc[i+1:]
            try:
                user, passwd = login_info.split(':', 1)
            except ValueError:
                user, passwd = "anonymous", None
        else:
            user, passwd = "anonymous", None
        #self.log_request()
        try:
            ftp = ftplib.FTP(netloc)
            ftp.login(user, passwd)
            if handler.command == "GET":
                ftp.retrbinary("RETR %s" % path, handler.connection.send)
            ftp.quit()
        except Exception, e:
            self.server.logger.log_warning("FTP Exception: %s" % e)


    def _proxying(self, handler):
        self._jambe.Log.log('url: %s' % str(handler._url))
        if handler._url.scheme not in('http', 'ftp') or handler._url.fragment:
            handler.send_error(400, "bad url %s" % self.path)
            return
        if handler._url.scheme == 'http':
            self._proxying_http(handler)
        elif handler._url.scheme == 'ftp':
            self._proxying_ftp(handler)

    def hook_HandlerHTTP_method_GET(self, handler):
        results = self._jambe.Mh.invoke_all('ProxyHTTP_method_GET_init', handler)
        if not True in results.values():
            self._proxying(handler)

def setup(jambe):
    return ProxyHTTP(jambe)

