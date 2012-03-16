#!/usr/bin/env python

#http://stackoverflow.com/questions/9734106/python-3-2-html-parser/9735733#9735733

from HTMLParser import HTMLParser

class DanParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.in_select = False

    def handle_starttag(self, tag, attrs):
        print("Start Tag: ", tag, attrs)
        if tag == "select":
            self.in_select = True
            print("Start Tag: ", tag, attrs)

    def handle_endtag(self, tag):
        print("EndTag: ", tag)
        if tag == "select" and self.in_select:
            self.in_select = False
            print("EndTag: ", tag)

    def handle_data(self, data):
        print("Data: ", data)
        if self.in_select:
            print("Data: ", data)

    def handle_startendtag(self,tag,attrs):
        print("StarEnd Tag: ", tag, attrs)

t = DanParser()
t.feed("<select>test</select>")
