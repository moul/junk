print __file__

def setup(jambe):
    jambe.variable_set('server_address', '127.0.0.1', True)
    jambe.variable_set('server_port', 8000, True)
    jambe.variable_set('log_level', 20, True)
