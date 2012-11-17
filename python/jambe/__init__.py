print __file__

__version__ = '0.0.1 beta'
__author__ = 'Manfred Touron'
#__all__ = ['libs', 'modules', 'config', 'boot']

##############################################################

DEFAULT_LOG_LEVEL = 20
DEFAULT_MAX_LOG_SIZE = 20
DEFAULT_MAX_LOG_SIZE = 20
DEFAULT_DB_URL = 'sqlite3://:memory:'
DEFAULT_ENABLED_MODULES = ['core']

##############################################################

class jambeException(BaseException):
    pass

##############################################################

class Jambe():
    BOOT_CONFIGURATION = 0
    BOOT_LOG = 1
    BOOT_CACHE = 2
    BOOT_DATABASE = 3
    BOOT_DAEMON = 4
    BOOT_MODULES = 5
    BOOT_CRON = 6
    BOOT_THEME = 7
    BOOT_FULL = 8

    ##########

    _version = __version__
    _author = __author__

    _variables = {}
    _phases = {}
    _phase = 0

    ##########

    Mh = None
    Logger = None

    ##########

    Exception = jambeException

    ##########

    def __init__(self):
        import os
        self._phases = {self.BOOT_CONFIGURATION: self._bootstrap_configuration,
                        self.BOOT_LOG: self._bootstrap_log,
                        self.BOOT_CACHE: self._bootstrap_cache,
                        self.BOOT_DATABASE: self._bootstrap_db,
                        self.BOOT_DAEMON: self._bootstrap_daemon,
                        self.BOOT_MODULES: self._bootstrap_modules,
                        self.BOOT_CRON: self._bootstrap_cron,
                        self.BOOT_THEME: self._bootstrap_theme,
                        self.BOOT_FULL: self._bootstrap_full}
        self._directory = os.path.realpath(os.path.join(__file__, '..'))

    def version(self, full = False):
        if full:
            return 'jambe %s' % self._version
        return self._version

    def variable_set(self, key, value, safe = False):
        if not safe or not key in self._variables:
            self._variables[key] = value

    def variable_unset(self, key):
        if key in self._variables:
            del self._variables[key]

    def variable_set_multiple(self, variables):
        for key in variables:
            self.variable_set(key, variables[key])

    def variable_get(self, key, default):
        return key in self._variables and self._variables[key] or default

    def bootstrap(self, phase):
        phases = self._phases.items()
        phases.sort()
        phases = dict(phases)

        while phase >= self._phase:
            if self._phase in phases:
                try:
                    phases[(self._phase)]()
                except self.Exception, e:
                    raise self.Exception('bootstrap error on phase "%s" with message: "%s"' % (phases[self._phase], e))
                del phases[self._phase]
            self._phase += 1

    def _bootstrap_configuration(self):
        config_name = self.variable_get('config_name', 'default')
        try:
            tmp = __import__("jambe.config.%s" % config_name)
        except:
            raise self.Exception('config file "%s" not found' % config_name)
        eval('tmp.config.%s.setup(self)' % config_name)
        del tmp
        print "[+] configuration"

    def _bootstrap_log(self):
        import jambe.libs.log
        self.Log = jambe.libs.log.setup(self)
#filename = logfile, log_size = logsize, daemon = daemon, log_level = log_level)
        self.Log.log("[+] log")

    def _bootstrap_cache(self):
        import jambe.libs.cache
        self.Cache = jambe.libs.cache.setup(self)
        self.Log.log('[+] cache')

    def _bootstrap_db(self, check_install = True, reload = False):
        import urlparse
        db_url = self.variable_get('db_url', DEFAULT_DB_URL)
        (scheme, netloc, path, params, query, fragment) = urlparse.urlparse(db_url)

        if not reload or not hasattr(self, '_db_imported') or not self._db_imported:
            try:
                tmp = __import__("jambe.libs.db_%s" % scheme)
            except ImportError, e:
                raise self.Exception('db type not supported: "%s" (%s)' % (scheme, e))
            self.Db = eval("tmp.libs.db_%s.setup(self)" % scheme)
            del tmp
            self._db_imported = True

        self.Db.connect(scheme = scheme, netloc = netloc, path = path, params = params, query = query, fragment = fragment)

        if check_install:
            if self.is_installed():
                self.uninstall()
            if not self.is_installed():
                self.install()
        self.Log.log("[+] db")

    def is_installed(self):
        return self.Db.table_exists('system')

    def _bootstrap_daemon(self):
        if self.variable_get('daemon', False):
            import jambe.libs.daemon
            jambe.libs.daemon.setup(self)
#daemon = True, logger = _logger)
        self.Log.log("[+] daemon")

    def __bootstrap_modules(self):
        import jambe.libs.modules
        if not self.Mh:
            self.Mh = jambe.libs.modules.setup(self)
        enabled_modules = self.variable_get('enabled_modules', DEFAULT_ENABLED_MODULES)
        self.Mh.load_modules(enabled_modules)

    def _bootstrap_modules(self):
        self.__bootstrap_modules()
        self.Mh.invoke_all('init')
        self.Log.log("[+] modules")

    def _bootstrap_cron(self):
        print 'NOT IMPLEMENTEDDD'
        self.Log.log("[+] cron")

    def _bootstrap_theme(self):
        import jambe.libs.theme
        self.Theme = jambe.libs.theme.setup(self)
        self.Mh.invoke_all('theme_init')
        self.Log.log("[+] theme")

    def _bootstrap_full(self):
        self.Log.log('[+] _bootstrap FULL')

    def uninstall(self):
        self.Log.log('Beginning uninstallation...')
        if not self.Mh:
            self.__bootstrap_modules()
        self.Mh.invoke_all('uninstall')
        self.Log.log('Jambe uninstalled')

    def install(self):
        self.Log.log('Beginning installation...')
        if not self.Mh:
            self.__bootstrap_modules()
        self.Mh.invoke_all('install')
        self.Log.log('Jambe installed')

    def routine(self):
        self.Log.log("[+] routine")

