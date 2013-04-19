#!/usr/bin/env coffee

{StatsD} = require 'node-statsd'
client = new StatsD
#  host: 'graphite...'

setInterval (->
  client.timing    'test_timing', 42
  client.increment 'test_counter'
  client.decrement 'test_counter'
  client.gauge     'test_gauge', 123.45
  client.set       'test_unique', 'foobar'
  client.unique    'test_unique', 'foobarbaz'
  client.increment ['test_multiple_1', 'test_multiple_2', 'test_multiple_3']
  client.increment 'test_counter', 1, 0.25
  ), 1000

console.log 'done'
