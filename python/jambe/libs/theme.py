print __file__

class Theme():
    _directories = {}
    _all_directories = []
    _cache_directories = {}
    _cache_files = {}
    _permanents = {}

    def __init__(self, jambe):
        self._jambe = jambe
        self._bla = 42

    def templates_directory_add(self, directory, type = 'module'):
        import os
        if not type in self._directories:
            self._directories[type] = []
        directory = os.path.join(self._jambe._directory, directory)
        directory = os.path.realpath(directory)
        self._jambe.Log.log('Templates directory "%s" add with type "%s"' % (directory, type))
        self._directories[type].append(directory)
        self._all_directories.append(directory)

    def theme(self, hook, args = {}):
        filecontent = self._template_file_cache('%s.html' % hook)
        if filecontent:
            return self._render_template(filecontent, args)
        hook = 'theme_%s' % hook
        results = self._jambe.Mh.invoke_all(hook, args)
        for result in results:
            return results[result]
        if hasattr(self, hook):
            return getattr(self, hook)(**args)
        return '{Theme %s not found}' % hook

    def theme_table(self, values = [], headers = None):
        content = '<table>'
        if headers:
            content += '<thead><tr>'
            for col in headers:
                content += '<td>%s</td>' % col
            content += '</tr><thead>'
        content += '<tbody>'
        for row in values:
            content += '<tr>'
            for col in row:
                content += '<td>%s</td>' % col
            content += '</tr>'
        content += '</tbody></table>'
        return content

    def erase_cache(self):
        self._cache_directories = {}
        self._cache_files = {}

    def set_permanent(self, name, value, type = 'all'):
        if not type in self._permanents:
            self._permanents[type] = {}
        self._permanents[type][name] = value

    def get_permanent(self, name, type = 'all'):
        return self._permanents[type][name]

    def preprocess(self, hook, args):
        hook = 'preprocess_%s' % hook
        if hasattr(self, hook):
            getattr(self, hook)(args)
        self._jambe.Mh.invoke_all(hook, args)

    def preprocess_page(self, args):
        for key in self._permanents['page']:
            if not key in args:
                args[key] = self._permanents['page'][key]
        
    def _template_file_cache(self, filename):
        import os
        found = False
        if not filename in self._cache_files:
            self._jambe.Log.log('%s was not found in cache' % filename)
            for directory in self._all_directories:
                if not directory in self._cache_directories:
                    self._jambe.Log.log('Caching directory listing for "%s"' % directory)
                    self._cache_directories[directory] = os.listdir(directory)
                if filename in self._cache_directories[directory]:
                    found = True
                    break
            self._cache_files[filename] = False
            if found:
                fullfilename = os.path.join(directory, filename)
                self._jambe.Log.log('Caching %s' % fullfilename)
                self._cache_files[filename] = file(fullfilename, 'r').read()
        return self._cache_files[filename]

    def _render_template(self, filecontent, args = {}):
        try:
            return filecontent % args
        except KeyError, e:
            return 'KeyError: %s' % e

    def render_template(self, filename, args = {}):
        filecontent = self._template_file_cache(filename)
        if filecontent:
            return self._render_template(filecontent, args)
        return 'Error'
        

def setup(jambe):
    return Theme(jambe)
