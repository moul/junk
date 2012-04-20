#!/usr/bin/env python

import sys
from scapy.all import *
ans, unans = srp(Ether(dst = "ff:ff:ff:ff:ff:ff")/ARP(pdst = sys.argv[1]), timeout = 2)

for snd, rcv in ans:
    print rcv.sprintf(r('%Ether.src% & %ARP.psrc%'))
