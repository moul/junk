combine = require 'stream-combiner'
through = require 'through'
split =   require 'split'
zlib =    require 'zlib'


module.exports = ->

  current = null

  grouper_write = (buf) ->
    return unless buf.length

    row = JSON.parse buf

    if row.type is 'genre'
      @queue "#{JSON.stringify(current)}\n" if current
      current =
        name:  row.name
        books: []
    else
      current.books.push row.name

  grouper_end = ->
    @queue "#{JSON.stringify(current)}\n" if current
    @queue null

  grouper = through grouper_write, grouper_end

  return combine split(), grouper, zlib.createGzip()
