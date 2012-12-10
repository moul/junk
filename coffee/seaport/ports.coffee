#!/usr/bin/env coffe

seaport = require 'seaport'

ports = seaport.createServer()
ports.listen 5001

ports.on 'register', (service) ->
    console.log 'register', service

console.log 'ok'
