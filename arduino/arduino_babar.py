#!/usr/bin/env python

from arduino_moul import Mouluino
from struct import *
from pprint import pprint
from time import sleep

class MouluinoBabar(Mouluino):
    def __init__(self):
        Mouluino.__init__(self)

    def set_mode_switch_color(self, color_from = 0xFF0000, color_to = 0x00FF00):
        #color_from = args.get(0, 0xFF0000)
        #color_to = args.get(1, 0x00FF00)
        self.write(pack('B', 0x0001))
        self.write(pack('I', color_from))
        self.write(pack('I', color_to))

    def set_mode_random(self):
        self.write(pack('B', 0x0002))

    def set_mode_blink(self, color = 0xff0088):
        self.write(pack('B', 0x0004))
        self.write(pack('I', color))

if __name__ == '__main__':
    babar = MouluinoBabar()

    queue = []
    queue.append(['set_mode_switch_color', 0x0000FF, 0xFF0000])

    sleep(2) #while not ready (voir si ya pas un truc qui fait ca)

    is_waiting = True
    while True:
        if is_waiting:
            if len(queue):
                action = queue[0]
                queue = queue[1:]
                apply(getattr(babar, action[0]), action[1:]);
                is_waiting = False
            else:
                print "Queue is empty !!"
        line = babar.readline().strip()
        print line
        if line == 'finished':
            is_waiting = True
