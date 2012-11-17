print __file__

import jambe.libs.modules

import time, random, hashlib, threading

class jambeNetsoulUser():
    location = '-'
    port = 0
    ip = ''
    message = ''
    login = ''
    thread = ''
    logged = False
    group = 'ext'
    status = 'active'
    id = 0
    idle_timestamp = 0
    login_timestamp = 0
    workstation_type = '~'

    def __init__(self, handler):
        self.handler = handler
        self.id = threading.current_thread().name[7:]
        self.md5 = hashlib.md5(str(random.Random().random())).hexdigest()
        (self.ip, self.port) = handler.client_address
        self.login_timestamp = int(time.time())
        self.idle_timestamp = int(time.time())
        #TODO: self.group = epitech_2011

    def user_cmd_str(self):
        datas = []
        datas.append(self.id) #socket
        datas.append('user') #user
        datas.append('todo') #trust level
        datas.append(self.login) #login
        datas.append(self.ip) #user host
        datas.append(self.workstation_type) #workstation type
        datas.append(self.location) #location
        datas.append(self.group) #group
        return ':'.join(datas)

    def list_users_str(self):
        datas = {}
        datas['port'] = self.id
        datas['login'] = self.login
        datas['ip'] = self.ip
        datas['login_timestamp'] = self.login_timestamp
        datas['idle_timestamp'] = self.idle_timestamp
        datas['auth_user'] = 42
        datas['auth_ag'] = 42
        datas['mach_func'] = 42
        datas['location'] = self.location
        datas['group'] = self.group
        datas['status'] = self.status
        datas['user_data'] = self.message
        return '%(port)s %(login)s %(ip)s %(login_timestamp)s %(idle_timestamp)s %(auth_user)s %(auth_ag)s %(mach_func)s %(location)s %(group)s %(status)s %(user_data)s' % datas

class jambeNetsoul(jambe.libs.modules.jambeModule):
    _dependencies = []
    _usersByLogin = {}
    _usersById = {}

    def hook_HandlerSocketByLine_setup(self, handler):
        netsoulUser = jambeNetsoulUser(handler)
        handler.netsoulUser = netsoulUser
        self._usersById[netsoulUser.id] = netsoulUser
        self._auth(handler)

    def hook_HandlerSocketByLine_client_disconnected(self, handler):
        id = handler.netsoulUser.id
        login = handler.netsoulUser.login
        del self._usersById[id]
        if login in self._usersByLogin:
            if id in self._usersByLogin[login]:
                del self._usersByLogin[login][id]

    def is_logged(self, handler):
        return handler.netsoulUser.logged

    def hook_HandlerSocketByLine_handle_one_request(self, handler, line):
        command = line.strip().split(' ')
        if hasattr(self, 'command_%s' % command[0]):
            getattr(self, 'command_%s' % command[0])(handler, line, command)
        else:
            handler._write('bad command\n')

    def command_auth_ag(self, handler, line, command):
        if self.is_logged(handler):
            handler._write('error not logged\n')
        else:
            handler._write('rep 002 -- cmd end\n')

    def command_ext_user_log(self, handler, line, command):
        if self.is_logged(handler):
            handler._write('error not logged\n')
        else:
            user = handler.netsoulUser
            login = command[1]
            challenge = command[2]
            if True:
                print 'TODO: ext_user_log'
                handler._write('rep 002 -- cmd end\n')
                location = command[3]
                message = command[4]
                handler.netsoulUser.logged = True
                if not login in self._usersByLogin:
                    self._usersByLogin[login] = {}
                self._usersByLogin[login][user.id] = user
                user.login = login
                user.location = location
                user.message = message
                print self._usersById
                print self._usersByLogin
            else:
                handler._write('ohnoes bad password\n')

    def command_watch_log_user(self, handler, line, command):
        print 'TODO: watch_log_user'

    def command_watch_who(self, handler, line, command):
        print 'TODO: who'

    def command_exit(self, handler, line, command):
        print 'TODO: exit'

    def command_list_users(self, handler, line, command):
        if len(command) > 1:
            raise notImplemented
        for user in self._usersById.values():
            if user.logged:
                handler._write(user.list_users_str() + '\n')
        handler._write('rep 002 -- cmd end\n')

    def command_ping(self, handler, line, command):
        handler._write('pong')

    def command_attach(self, handler, line, command):
        if self.is_logged(handler):
            handler._write('rep 002 -- cmd end\n')
        else:
            handler._write('error not logged lolz\n')

    def _parse_dests(self, dests):
        if dests[0] == '{':
            return dests[1:-1].split(',')
        else:
            return [dests]

    def user_cmd_state(self, handler, line, command):
        id = handler.netsoulUser.id
        self._usersById[id].status = command[2]
        handler._write('rep 002 -- cmd end\n')

    def _users_by_dests(self, dests):
        dests = self._parse_dests(dests)
        users = {}
        #print "usersById: ", self._usersById
        #print "usersByLogin: ", self._usersByLogin
        #print "dests: ", dests
        for dest in dests:
            if dest[0] == ':':
                id = dest[1:]
                if id in self._usersById:
                    users[id] = self._usersById[id]
            else:
                login = dest
                if login in self._usersByLogin:
                    for key, value in self._usersByLogin[login].items():
                        users[key] = value
        return users

    def user_cmd_msg_user(self, handler, line, command):
        for id, user in self._users_by_dests(command[2]).items():
            user.handler._write('user_cmd %s | msg %s\n' % (user.user_cmd_str(), command[4]))
        handler._write('rep 002 -- cmd end\n')

    def command_user_cmd(self, handler, line, command):
        if self.is_logged(handler):
            if hasattr(self, 'user_cmd_%s' % command[1]):
                getattr(self, 'user_cmd_%s' % command[1])(handler, line, command)
            else:
                handler._write('bad command\n')            
        else:
            handler._write('error not logged lolz\n')

    def _auth(self, handler):
        user = handler.netsoulUser
        self._jambe.Log.log('handler socket by line auth')
        handler._write('salut %s %s %s %s %s\n' % (user.id, user.md5, user.ip, user.port, user.login_timestamp))

def setup(jambe):
    return jambeNetsoul(jambe)
