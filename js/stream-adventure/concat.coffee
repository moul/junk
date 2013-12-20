concat = require 'concat-stream'

c = concat (body) ->
  console.log body.toString().split("").reverse().join("")

process.stdin.pipe(c)
