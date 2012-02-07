import hashlib, urllib
from time import time

class nsException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class ns:
    "Netsoul object"
    def __init__(self, socket = False, socket_file = False, debug = None):
        self.connected = False
        self.socket = socket
        self.debug = debug
        self.unix_socket = False
        self.socket_file = socket_file
        if self.socket and not self.socket_file:
            self.socket_file = self.socket.makefile()
        hello = self._readline().split()
        self.hello = { "code": hello[1],
                       "md5": hello[2],
                       "ip": hello[3],
                       "port": hello[4],
                       "timestamp": hello[5] }

    def _readline(self, mute = False, strip = True):
        data = self.socket_file.readline()
        if strip:
            data = data.strip()
        if not mute and self.debug:
            self.debug('< %s' % data)
        return data

    def _recv(self, mute = False, strip = True):
        data = self.socket.recv(2048)
        if strip:
            data = data.strip()
        if not mute and self.debug:
            self.debug('< %s' % data)
        return data

    def _send(self, msg, mute = False):
        if not mute and self.debug:
            self.debug('> %s' % msg)
        self.socket.send('%s\n' % msg)

    def connect(self, location = '-', agent = '-', username = '-', password = '-', status = 'actif'):
        if self.connected:
            self.debug("Already connected")
        else:
            self._send('auth_ag ext_user none none')
            if self._readline() == "rep 002 -- cmd end":
                self._send("ext_user_log %s %s %s %s" % (username, hashlib.md5("%s-%s/%s%s" % (self.hello['md5'], self.hello['ip'], self.hello['port'], password)).hexdigest(), location, agent))
                if self._readline().split()[1] == '002':
                    self._send('user_cmd state %s:%d' % (status, time()))
                    self._send('attach')
                    self.connected = True
                    return True
                else:
                    raise nsException("Identification failed")
            else:
                raise nsException("Not allowed to log in")

    def list_users(self, lst = None):
        "fait comme list_user_iter, mais sans iteration"
        return list(self.list_users_iter(lst))

    def list_users_iter(self, list = None):
        if list:
            self._send("list_users %s" % list)
        else:
            self._send("list_users")
        users = []
        while True:
            try:
                lineraw = self._readline()
            except:
                break
            if lineraw == "" or lineraw == "rep 002 -- cmd end":
                break
            line = lineraw.split(' ')
            status = line[10].split(':') + [0]
            if len(line) == 12 and all(map(len, line)):
                yield {"port": int(line[0]),
                       "login": line[1],
                       "ip": line[2],
                       "login_timestamp": line[3],
                       "idle_timestamp": line[4],
                       "auth_user": int(line[5]),
                       "auth_ag": int(line[6]),
                       "mach_func": line[7],
                       "location": line[8],
                       "group": line[9],
                       "status_type": status[0],
                       "status_time": int(status[1]),
                       "agent": line[11],
                       "raw": lineraw}
            else:
                print "Error: %s" % lineraw
