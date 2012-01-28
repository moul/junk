#!/usr/bin/env python

from arduino_moul import *
from arduino_rgbled import *
from pprint import pprint
from time import sleep
from moulCurves import *
import sys

class MouluinoPiezo(MouluinoSMS):
    def __init__(self, pin = 0):
        self.pin = pin
        MouluinoSMS.__init__(self)
        print "bbb"

class MouluinoPiezoRGB(MouluinoSMSRgbled, MouluinoPiezo):
    def __init__(self, pins, pin):
        MouluinoSMSRgbled.__init__(self, pins)
        MouluinoPieze.__init__(self, pin)
        print "aaaa"

if __name__ == '__main__':
    arduino = MouluinoPiezo(pin = 0)

    while True:
        print arduino.read_analogs()
        #print arduino.read_digitals()
        sleep(.1)
    sleep(10)
