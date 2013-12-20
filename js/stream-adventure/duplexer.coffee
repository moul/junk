{spawn} = require 'child_process'
duplex = require 'duplexer'

module.exports = (cmd, args) ->
  ps = spawn cmd, args
  return duplex ps.stdin, ps.stdout
