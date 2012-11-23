#!/usr/bin/env coffee

seaport = require 'seaport'
bouncy = require 'bouncy'

ports = seaport.createServer()
ports.listen 5001

bouncy((req, bounce) ->
    service = 'static'

    if req.url.match /^\/socket.io\/1/
        service = 'pusher'
    #else if req.method.toLowerCase() is 'post'
    #    service = 'downloader'

    domains = (req.headers.host || '').split('.')
    versions =
        unstable: '1.1.x'
        stable: '1.0.x'
    selectedVersion = versions[domains[0]] || '1.0.x'
    fullService = "#{service}@#{selectedVersion}"

    ps = ports.query fullService

    if not ps.length
        res = bounce.respond()
        res.end 'service not available'
    else
        #bounce(ps[0].host, ps[0].port)

        worker = ps[Math.floor(Math.random() * ps.length)]
        bounce(worker.host, worker.port)

).listen 5000