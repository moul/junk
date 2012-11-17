print __file__

DEFAULT_NAMESPACE = 'cache'

class jambeCache():
    def __init__(self, jambe):
        self._jambe = jambe

    def cache_get(self, key):
        raise todo

    def cache_set(self, key, value, namespace = DEFAULT_NAMESPACE):
        raise todo

    def cache_del(self, key, namespace = DEFAULT_NAMESPACE):
        raise todo

def setup(jambe):
    return jambeCache(jambe)
