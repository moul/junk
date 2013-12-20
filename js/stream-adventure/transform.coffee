through = require 'through'

write = (buf) -> @queue buf.toString().toUpperCase()

tr = through write

process.stdin.pipe(tr).pipe(process.stdout)
