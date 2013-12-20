through = require 'through'
split = require 'split'

i = 1
write = (line) ->
  i = 1 - i
  @queue if i then "#{line.toUpperCase()}\n" else "#{line.toLowerCase()}\n"

tr = through write

process.stdin.pipe(split()).pipe(tr).pipe(process.stdout)
