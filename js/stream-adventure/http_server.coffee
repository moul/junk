http = require 'http'
through = require 'through'

tr = through (buf) ->
  @queue buf.toString().toUpperCase()

server = http.createServer (req, res) ->
  if req.method is 'POST'
    req.pipe(res)

server.listen process.argv[2]