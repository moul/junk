#!/usr/bin/env coffee

path = require 'path'
forever = require 'forever-monitor'

['router', 'static', 'static', 'pusher', 'downloader'].forEach (name) ->
    file = "#{name}.coffee"
    filePath = path.join __dirname, file
    child = new (forever.Monitor) filePath,
        silent: process.env.NODE_ENV == 'production'

    do child.start

    child.on 'start', ->
        console.log "#{file} has been started"

    child.on 'restart', ->
        console.log "#{file} has been restarted"

    child.on 'exit', ->
        console.log "#{file} has exited after 3 restarts"
