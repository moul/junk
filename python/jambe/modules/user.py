print __file__

import jambe.libs.modules

class User(jambe.libs.modules.jambeModule):
    _dependencies = ['core']

    def hook_install_schemas(self):
        schemas = {}
        schemas['users'] = {'name': 'users',
                            'fields':
                                {'uid':
                                     {'type': 'serial',
                                      'unsigned': True,
                                      'not null': True},
                                 'name':
                                     {'type': 'varchar',
                                      'length': 60,
                                      'not null': True,
                                      'default': ''},
                                 'pass':
                                     {'type': 'varchar',
                                      'length': 32,
                                      'not null': True,
                                      'default': ''},
                                 'mail':
                                     {'type': 'varchar',
                                      'length': 64,
                                      'not null': False,
                                      'default': ''},
                                 'created':
                                     {'type': 'int',
                                      'not null': True,
                                      'default': 0},
                                 'access':
                                     {'type': 'int',
                                      'not null': True,
                                      'default': 0},
                                 'login':
                                     {'type': 'int',
                                      'not null': True,
                                      'default': 0},
                                 'status':
                                     {'type': 'int',
                                      'not null': True,
                                      'size': 'tiny',
                                      'default': 1},
                                 'groups':
                                     {'type': 'varchar',
                                      'length': 255,
                                      'not null': True,
                                      'default': ''},
                                 'data':
                                     {'type': 'text',
                                      'size': 'big',
                                      'not null': False}},
                            'primary key': ['uid'],
                            'indexes': {'access': ['access'],
                                        'created': ['created'],
                                        'mail': ['mail']},
                            'unique keys': {'name': ['name']}}
        return schemas

    def _password_hash(self, password):
        return password

    def users_list(self, where = None, fields = ['uid', 'name']):
        return self._jambe.Db.select('users').where(where).fields(fields).execute().fetch_all()

    def users_del(self, where = {}):
        raise notImplementedError

    def hook_admin_init(self, admin):
        admin._links.append({'path': '/users', 'title': 'Users', 'callback': self._admin_users})

    def _admin_users(self):
        content = ''
        fields = ['uid', 'name', 'groups']
        users = self.users_list(fields = fields)
        return self._jambe.Theme.theme('table', {'values': users, 'headers': fields})

    def user_add(self, args = {}):
        print
        import time
        import json
        self._jambe.Log.log('Adding user %s' % args['name'])

        if 'uid' in args:
            pass
        else:
            args['created'] = int(time.time())
            args['pass'] = self._password_hash(args['pass'])

        if 'groups' in args:
            args['groups'] = ','.join(args['groups'])


        fields = []
        values = []
        for key in ['name', 'pass', 'mail', 'created', 'access', 'login', 'status', 'groups', 'data']:
            if key in args:
                fields.append(key)
                values.append(args[key])
                del args[key]

        fields.append('data')
        values.append(json.dumps(args))

        insert = self._jambe.Db.insert('users').fields(fields).values(values).execute()

    def user_load(self, where = {}):
        select = self._jambe.Db.select('users').execute().fetch_one()
        print select
        raise notImplementedError

    def hook_install(self):
        jambe.libs.modules.jambeModule.hook_install(self)

        users = []
        users.append({'name': 'moul', 'pass': 'password', 'groups': ['admin', 'proxy']})
        users.append({'name': 'admin', 'pass': 'password', 'groups': ['admin']})
        users.append({'name': 'proxy', 'pass': 'password', 'groups': ['proxy']})
        for user in users:
            self.user_add(user)

def setup(jambe):
    return User(jambe)
