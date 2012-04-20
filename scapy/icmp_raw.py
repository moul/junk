#!/usr/bin/env python

import sys
from scapy.all import *

#conf.iface = 'wmnet8'

p = sr1(IP(dst = sys.argv[1])/ICMP())
if p:
    p.show()
