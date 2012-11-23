#!/usr/bin/env coffee

seaport = require 'seaport'
express = require 'express'
http = require 'http'

ports = seaport.connect 'localhost', 5001

app = do express

app.get '/', (req, res) ->
    res.json ports.ports

server = http.createServer app

#io = io.listen server

server.listen ports.register 'static@1.0.1'
