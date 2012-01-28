#!/usr/bin/env python

import arduino_moul

am = arduino_moul.ArduinoMoul()

while True:
    print am.readline().strip()
