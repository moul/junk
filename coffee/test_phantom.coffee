#!/usr/bin/env phantomjs

page = require('webpage').create()

page.open 'http://www.google.com/', (status) ->
    console.log status
    console.log page
    do phantom.exit
