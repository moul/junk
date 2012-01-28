#!/usr/bin/env python

from arduino_moul import MouluinoSMS
from struct import *
from pprint import pprint
from time import sleep

if __name__ == '__main__':
    sms = MouluinoSMS()
    sms.write_analog(5, 255)
    print sms.read_analog(5)
    sleep(10);
