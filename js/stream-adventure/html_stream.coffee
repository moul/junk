trumpet = require 'trumpet'
through = require 'through'

tr = trumpet()

loud = tr.select('.loud').createStream()
th = through (buf) ->
  @queue buf.toString().toUpperCase()

loud.pipe(th).pipe(loud)

process.stdin.pipe(tr).pipe(process.stdout)
