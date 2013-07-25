#!/usr/bin/env python

# curl http://bob:bib@localhost:8080/?bub=bab

import cherrypy

class Custom(object):
    def index(self, bub = 'default_bub'):
        if cherrypy.request.params.get('bub', False):
            if cherrypy.request.params['bub'] == 'bab':
                return 'bub=bab !'
            else:
                return 'bad bub'
        if cherrypy.request.login == 'bob:bib': # dont work, needs to use cherrypy.request.headers['Authorization']
            return 'hello bob:bib'
        return 'default'
    index.exposed = True

cherrypy.quickstart(Custom())
