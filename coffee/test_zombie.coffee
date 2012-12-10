Browser = require 'zombie'

browser = new Browser()
browser.visit 'http://www.google.com/', ->
    browser.fill 'q', 'test'
    browser.pressButton 'Recherche Google', ->
        #console.log browser.html()
        #console.log browser.body
        #console.log browser.html '.g .l.vst'
        console.log browser.queryAll 'div'
        #browser.body.queryAll('.g .l.vst')
