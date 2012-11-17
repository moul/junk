print __file__

DEFAULT_LOG_NAME = 'jambe'
DEFAULT_LOG_FILENAME = 'jambe.log'
DEFAULT_LOG_FORMAT = "[%(asctime)-12s.%(msecs)03d] %(levelname)-8s {%(name)s %(threadName)s} %(message)s"
DEFAULT_LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S"

class jambeLog():
    CRITICAL = 50
    DEBUG = 10
    ERROR = 40
    FATAL = 50
    INFO = 20
    NOTSET = 0
    WARN = 30
    WARNING = 30

    def __init__(self, jambe):
        import logging
        self._jambe = jambe
        log_name = jambe.variable_get('loggerName', DEFAULT_LOG_NAME)
        filename = jambe.variable_get('log_filename', None)
        daemon = jambe.variable_get('daemon', False)
        log_level = jambe.variable_get('log_level', 20)
        log_size = jambe.variable_get('log_size', 20)
        self._logger = logging.getLogger(log_name)
        self._logger.setLevel(log_level)
        self._handler = False
        if not filename:
            if not daemon:
                self._handler = logging.StreamHandler()
            else:
                filename = DEFAULT_LOG_FILENAME
        if not self._handler:
            import logging.handlers
            self._handler = logging.handlers.RotatingFileHandler(filename, maxBytes = (log_size * (1 << 20)), backupCount = 5)
        fmt = logging.Formatter(DEFAULT_LOG_FORMAT, DEFAULT_LOG_TIME_FORMAT)
        self._handler.setFormatter(fmt)
        self._logger.addHandler(self._handler)

    def log(self, msg, level = INFO):
        self._logger.log(level, msg)

def setup(jambe):
    return jambeLog(jambe)
