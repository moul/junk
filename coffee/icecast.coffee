#!/usr/bin/env coffee

http = require 'http'
url = 'http://stream.onouo.com:8000'
icecast = require 'icecast-stack'
stream = icecast.createReadStream url

clients = []
stream.on 'connect', ->
    console.error 'radio stream connected !'

stream.on 'response', (res) ->
    console.error 'radio stream response !'
    console.error res.headers

stream.on 'data', (chunk) ->
    if clients.length > 0
        for client in clients
            clients[client].write chunk

stream.on 'metadata', (metadata) ->
    title = icecast.parseMetadata(metadata).StreamTitle
    console.error title

server = http.createServer (req, res) ->
    res.writeHead 200, {
        "Content-Type": "audio/mpeg",
        "Transfer-Encoding": "chunked"
        }
    clients.push res
    console.log 'Client connected; streaming'
server.listen "9000", "127.0.0.1"

console.log "Server running at http://127.0.0.1:9000"
