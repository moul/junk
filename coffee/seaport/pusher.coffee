#!/usr/bin/env coffee

seaport = require 'seaport'
http = require 'http'

ports = seaport.connect 'localhost', 5001

server = do http.createServer

ports.register 'pusher@1.0.0', (port, ready) ->
    server.listen port, ready