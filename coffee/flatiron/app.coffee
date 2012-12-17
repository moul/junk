#!/usr/bin/env coffee

flatiron = require 'flatiron'
app = flatiron.app

app.use flatiron.plugins.cli,
    dir: __dirname
    usage: [
        ''
        'test - This is a test.'
        ''
        'Usage:'
        ''
        '     test hello'
        '     test time'
        ''
        ]

commands =
    hello: ->      console.log 'hello world'
    prompt: ->
        app.prompt.get 'name', (err, result) ->
            app.log.info "prompting #{result.name}"
    say: (arg) ->  console.log 'saying', arg
    def: (arg) ->        console.log 'default', arg

app.cmd 'hello',    commands.hello
app.cmd /prompt/,   commands.prompt
app.cmd /say (.+)/, commands.say
app.cmd /(.+)/,     commands.def

app.start()
