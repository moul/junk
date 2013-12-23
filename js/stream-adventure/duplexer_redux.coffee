duplexer = require 'duplexer'
through = require 'through'

module.exports = (counter) ->

  counts = {}

  write = (row) ->
    counts[row.country] = (counts[row.country] or 0) + 1
    console.log counts

  end = ->
    counter.setCounts counts

  input = through write, end

  duplex = duplexer input, counter

  return duplex
