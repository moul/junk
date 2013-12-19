fs = require 'fs'

input = process.argv[2]
stream = fs.createReadStream input
stream.pipe process.stdout
