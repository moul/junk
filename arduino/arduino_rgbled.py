#!/usr/bin/env python

from arduino_moul import MouluinoSMS
from struct import *
from pprint import pprint
from time import sleep
from moulCurves import *
import sys

def parse_html_color(html_color):
    if html_color[0] == '#':
        html_color = html_color[1:]
    rgb = [int(html_color[:2], 16), int(html_color[2:4], 16), int(html_color[4:], 16)]
    return rgb

def set_opacity(color, opacity):
    newcolor = [0, 0, 0]
    for i in xrange(3):
        newcolor[i] = color[i] * opacity / 255
    return newcolor

class MouluinoSMSRgbled(MouluinoSMS):
    def __init__(self,  pins = [0, 0, 0]):
        MouluinoSMS.__init__(self)
        self.pins = pins
        self.current = [-1, -1, -1]
        for pin in pins:
            self.write_analog(pin, 0)

    def set_html_color(self, html_color, opacity = None):
        color = parse_html_color(html_color)
        if opacity is not None and opacity != 255:
            color = set_opacity(color, opacity)
        self.set_color(color)

    def set_color(self, color, opacity = None, sleep_time = .01):
        if opacity is not None:
            color = set_opacity(color, opacity)
        for i in xrange(3):
            if color[i] != self.current[i]:
                self.write_analog(self.pins[i], color[i])
                self.current[i] = color[i]
                sleep(sleep_time / 3)
        #print self.current

    def fadeOpacity(self, color, curve = None):
        print "fadeOpacitying color %s" % (color)
        if curve is None:
            curve = CurveLinear(limit = -1).iter
        for opacity in curve():
            self.set_color(color, opacity = opacity)

    def fadeColor(self, color_from, color_to, curve = None):
        print "fadeColoring from %s to %s" % (color_from, color_to)
        if curve is None:
            curve = CurveLinear(limit = -1).iter
        diff = [0, 0, 0]
        for i in xrange(3):
            diff[i] = color_to[i] - color_from[i]
        color = [0, 0, 0]
        for rate in curve():
            for i in xrange(3):
                color[i] = color_from[i] + diff[i] * rate / 255
            #print '%s = %s + %s * %s / 255' % (color, color_from, diff, rate)
            self.set_color(color)

if __name__ == '__main__':
    #testCurves()

    arduino = MouluinoSMSRgbled(pins = [3, 5, 6])


    arduino.fadeColor(parse_html_color('#FF0000'), parse_html_color('#00FFFF'));
    arduino.fadeColor(list(arduino.current), parse_html_color('#0000FF'));
    arduino.fadeColor(list(arduino.current), parse_html_color('#FF00FF'));
    arduino.fadeColor(list(arduino.current), parse_html_color('#FFFFFF'));
    arduino.fadeOpacity(list(arduino.current))
    #sleep(3);

    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveLinear(inc = 10, limit = 200).iter)
    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveTriangle(inc = 10, limit = 200).iter)
    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveCos(inc = .1, limit = 200).iter)
    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveRandom(inc = 30, limit = 200).iter)
    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveSin(inc = .1, limit = 200).iter)
    arduino.fadeOpacity(parse_html_color('#00FF00'), CurveSin(inc = .1, limit = 200).iter)
    arduino.set_color([255, 255, 255])
    sleep(1)
    arduino.fadeOpacity(parse_html_color('#FF0088'), CurveRandNear(inc = 30, limit = 20000).iter)
    sleep(10)
