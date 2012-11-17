print __file__

"""
reload(module)
"""

class jambeModule():
    _weight = 0
    _dependencies = []

    def __init__(self, jambe):
        self._jambe = jambe
        for dependency in self._dependencies:
            self._jambe.Mh.load_module(dependency)

    def hook_install(self):
        if hasattr(self, 'hook_install_schemas'):
            self._jambe.Db.install_from_schemas(self.hook_install_schemas())

    def hook_uninstall(self):
        if hasattr(self, 'hook_install_schemas'):
            try:
                self._jambe.Db.uninstall_from_schemas(self.hook_install_schemas())
            except:
                pass

class jambeModuleHandler():
    _enabled_modules = {}
    _enabled_modules_by_weight = {}
    _enabled_modules_by_weight_sorted = {}
    _weight = 0
    _cache_hook = {}
    _registered_modules = []

    def __init__(self, jambe):
        self._jambe = jambe

    def list_modules(self):
        return self._enabled_modules

    def load_modules(self, modules):
        for module in modules:
            self.load_module(module)

    def load_module(self, module):
        if module in self._registered_modules:
            return
        import imp
        try:
            tmp = __import__('jambe.modules.%s' % module)
        except ImportError, e:
            raise self._jambe.Exception("import error: %s" % e)
        object = eval('tmp.modules.%s.setup(self._jambe)' % module)
        del tmp
        if hasattr(object, '_weight'):
            weight = object._weight
            self._register(module, object, weight)
        else:
            self._register(module, object)
        self._jambe.Log.log('module "%s" registered' % module)
        self._registered_modules.append(module)

    def _register(self, name, object, weight = None):
        if not weight:
            weight = self._weight
            self._weight += 1
        while weight in self._enabled_modules_by_weight:
            weight += 0.0001
        self._enabled_modules[name] = self._enabled_modules_by_weight[weight] = {'name': name, 'object': object, 'weight': weight, 'status': 1}
        self._enabled_modules_by_weight_sorted = self._enabled_modules_by_weight.items()
        self._enabled_modules_by_weight_sorted.sort()

    def invoke(self, module, hook, *args):
        hook = 'hook_%s' % hook
        object = self._enabled_modules[module]['object']
        if not check or hasattr(object, hook):
            self._jambe.Log.log("invoking %s::%s" % (module, hook))
            return getattr(object, hook)(*args)

    def invokable(self, hook):
        #hook = 'hook_%s' % hook
        if not hook in self._cache_hook:
            self._cache_hook[hook] = []
            for weight, module in self._enabled_modules_by_weight_sorted:
                if hasattr(module['object'], hook):
                    self._cache_hook[hook].append(module)
        #self._jambe.Log.log('registered modules: %s' % ', '.join([module['name'] for weight, module in self._enabled_modules_by_weight_sorted]))
        return self._cache_hook[hook]

    def invoke_all(self, hook, *args):
        hook = 'hook_%s' % hook
        modules = self.invokable(hook)
        self._jambe.Log.log('invoke_all(%s) - %s' % (hook, ', '.join([module['name'] for module in modules])))
        results = {}
        for module in modules:
            results[module['name']] = getattr(module['object'], hook)(*args)
        return results

def setup(jambe):
    return jambeModuleHandler(jambe)

