print __file__

import jambe.libs.modules

DEFAULT_ADMIN_HOSTNAME = 'admin.jambe'

class jambeAdminResponse():
    args = {}
    headers = {}
    handler = None

class jambeAdmin(jambe.libs.modules.jambeModule):
    _dependencies = ['user', 'core']
    _links = []
    _path = '/'
    _admin_hostnames = [DEFAULT_ADMIN_HOSTNAME]
    _response = jambeAdminResponse

    def __init__(self, _jambe):
        jambe.libs.modules.jambeModule.__init__(self, _jambe)
        self._links.append({'path': '/', 'title': 'Home', 'callback': self._path_home})
        self._links.append({'path': '/modules', 'title': 'Modules', 'callback': self._path_modules})
        self._links.append({'path': '/test', 'title': 'Test', 'callback': self._path_test})
        self._links.append({'path': '/info', 'title': 'Info', 'callback': self._path_info})

        self._links.append({'path': '/proxies', 'title': 'Proxies'})
        self._links.append({'path': '/scenarios', 'title': 'Scenarios'})
        self._links.append({'path': '/history', 'title': 'History'})
        self._links.append({'path': '/log', 'title': 'Log'})
        self._links.append({'path': '/filters', 'title': 'Filters'})

    def hook_init(self):
        self._jambe.Mh.invoke_all('admin_init', self)

    def _path_home(self):
        return "HOME"

    def _path_modules(self):
        return "MODULES"

    def _path_test(self):
        return "TEST"

    def _path_info(self):
        return "INFO"

    def _menu(self, args = {}):
        menu = '<div id="menu"><h3>Menu</h3><ul>'
        for link in self._links:
            link['class'] = 'link'
            if 'path' in args and link['path'] == args['path']:
                link['class'] += ' active'
            menu += '<li class="%(class)s"><a href="%(path)s">%(title)s</a></li>' % link
        menu += '</ul></div>'
        return menu

    def hook_theme_admin_page(self, args):
        self._jambe.Theme.preprocess('page', args)
        return self._jambe.Theme.theme('_admin_page', args)

    def hook_preprocess_page(self, args):
        args['left'] += self._menu(args)
        if 'left' in args and len(args['left']):
            args['left'] = '<div id="left">%s</div>' % args['left']
        if 'right' in args and len(args['right']):
            args['right'] = '<div id="right">%s</div>' % args['right']
        if 'footer' in args and len(args['footer']):
            args['footer'] = '<div id="footer">%s</div>' % args['footer']

    def _get_active_handler(self, url, handler = None):
        for link in self._links:
            if link['path'] == url.path:
                return link
        return False

    def _execute_active_handler(self, url, handler):
        response = self._response()
        #response.http_handler = handler
        #response.request_url = url
        link = self._get_active_handler(url)
        if link:
            response.args['path'] = handler._url.path
            response.args['title'] = link['title']
            response.headers['Expires'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
            response.headers['Last-Modified'] = 'Sun, 25 Jan 1988 13:15:00 GMT'
            response.headers['Cache-Control'] = 'must-revalidate'
            response.headers['X-Powered-By'] = 'jambe'
            self._jambe.Mh.invoke_all('admin_handle_page_before', response)
            if 'callback' in link:
                response.args['content'] = link['callback']()
            else:
                response.args['content'] = 'Callback does not exists'
            self._jambe.Mh.invoke_all('admin_handle_page_after', response)
            response.content = self._jambe.Theme.theme('admin_page', response.args)
            response.code, response.message = 200, 'OK'
            self._jambe.Mh.invoke_all('admin_send_page_before', response)
            result = response.send()
            self._jambe.Mh.invoke_all('admin_send_page_after', response)
        else:
            response.code, response.message = 404, 'Page not Found'
        return response

    def hook_ProxyHTTP_method_GET_init(self, handler):
        if handler._url.netloc and not handler._url.netloc in self._admin_hostnames:
            return
        response = self._execute_active_handler(handler._url, handler)
        handler.send_response(response)

    def hook_theme_init(self):
        self._jambe.Theme.templates_directory_add('modules/admin/templates')
        self._jambe.Theme.set_permanent('head', '', type = 'page')
        self._jambe.Theme.set_permanent('script', '', type = 'page')
        self._jambe.Theme.set_permanent('left', '', type = 'page')
        self._jambe.Theme.set_permanent('right', '', type = 'page')
        self._jambe.Theme.set_permanent('footer', self._jambe.version(True), type = 'page')
        self._jambe.Theme.set_permanent('style', """<style>
      html, body { background: black; color: #ddd; font-family: Arial; font-size: 0.9em }
      #left, #center, #right { display: inline-block; padding: 20px 40px; margin: 20px; background: #222; vertical-align: top }
      #menu li.active a, a:hover { color: white }
      #left, #right { width: 145px }
      #center { width: 505px; min-height: 2 900px }
      #center h1 { background: #000; padding: 5px 20px }
      a { color: orange; text-decoration: none }
      #footer { color: gray; font-size: 0.8em; text-align: right; background: #222; padding: 10px 20px; width: 815px; margin: 20px }
      #page { width: 900px; margin: auto }
      table td { border-bottom: 1px solid black }
      table thead td { border-bottom: 3px solid black; font-weight: bold }
      table { font-size: small }
      .odd { background: #224 }
      .even { background: #422 }
      table { width: 100%% }
    </style>""", type = 'page')


def setup(jambe):
    return jambeAdmin(jambe)
