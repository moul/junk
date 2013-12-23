crypto = require 'crypto'

stream = crypto.createDecipher('aes256', process.argv[2])

process.stdin.pipe(stream).pipe(process.stdout)
