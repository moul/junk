print __file__

def setup(jambe):
    jambe.variable_set('server_address', '127.0.0.1')
    jambe.variable_set('server_port', 8000)
    jambe.variable_set('log_level', 1)
    jambe.variable_set('enabled_modules', ['proxy_http', 'admin', 'core', 'session', 'user'])
#jambe.variable_set('db_url', 'sqlite3://:memory:')
    jambe.variable_set('db_url', 'sqlite3://jambe.sqlite3')

config = {'users':
              {'moul': {'username': 'moul', 'password': 'password', 'groups': ['admin', 'requesters', 'proxy']},
               'm1ch3l': {'username': 'm1ch3l', 'password': 'password', 'groups': ['requesters', 'proxy']},
               }
          }
