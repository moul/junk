print __file__

import jambe.libs.modules

class jambeSessionObject():
    def __init__(self, sid = '', uid = 0, hostname = '', timestamp = None, session = {}):
        self.sid = sid
        self.uid = uid
        self.hostname = hostname
        self.timestamp = timestamp
        self.session = session

    def save(self):
        raise todo

class jambeSessionHandler(jambe.libs.modules.jambeModule):
    _dependencies = ['user', 'core']
    _sessionObject = jambeSessionObject

    def hook_install_schemas(self):
        schemas = {}
        schemas['sessions'] = {'name': 'users',
                               'fields':
                                   {'uid':
                                        {'type': 'int',
                                         'unsigned': True,
                                         'not null': True},
                                    'sid':
                                        {'type': 'varchar',
                                         'length': 64,
                                         'not null': True,
                                         'default': ''},
                                    'hostname':
                                        {'type': 'varchar',
                                         'length': 128,
                                         'not null': True,
                                         'default': ''},
                                    'timestamp':
                                        {'type': 'int',
                                         'not null': True,
                                         'default': 0},
                                    'session':
                                        {'type': 'text',
                                         'size': 'big',
                                         'not null': False}},
                               'primary key': ['sid'],
                               'indexes': {'timestamp': ['timestamp'],
                                           'uid': ['uid']}}
        return schemas

    def _admin_sessions(self):
        content = ''
        fields = ['uid', 'sid', 'hostname', 'timestamp']
        sessions = self.sessions_list(fields = fields)
        return self._jambe.Theme.theme('table', {'values': sessions, 'headers': fields})

    def hook_admin_handle_page_before(self, handler):
        self.session_start()

    def sessions_list(self, where = None, fields = ['uid', 'sid', 'hostname', 'timestamp']):
        return self._jambe.Db.select('sessions').where(where).fields(fields).execute().fetch_all()

    def get_sid(self):
        raise notimplementederror

    def session_new(self, uid = 0, hostname = '', session = {}):
        return self.sessionObject(sid = self.get_sid(), uid = uid, hostname = hostname, session = session)

    def session_start(self):
        session = self.session_load()
        if session:
            return session
        return self.session_new()

    def session_load(self, sid = None):
        if not sid:
            sid = self.get_sid()
        print key
        return False

    def hook_admin_init(self, admin):
        admin._links.append({'path': '/sessions', 'title': 'Sessions', 'callback': self._admin_sessions})
        pass

def setup(jambe):
    return jambeSessionHandler(jambe)
