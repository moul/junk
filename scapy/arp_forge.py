#!/usr/bin/env python

from scapy.all import *

SPORT = 10422
SRCIP = "1.2.3.4"
DSTIP = "192.168.63.129"

print conf.iface
#conf.iface = 'en0'

a = ARP()
a.display()
#a.hwsrc = "12:34:56:78:9a:bc"
#a.hwdst = "ff:ff:ff:ff:ff:ff"
a.pdst  = DSTIP
a.psrc  = SRCIP
send(a)

#eth = Ether(src = a.hwsrc, dst = "23:45:67:89:ab:cd")
#ip = IP(src = SRCIP, dst = DSTIP, flags = "DF", ttl = 64)
#tcpopt = [ ("MSS", 1460), ("NOP", None) ]
#SYN = TCP(sport = SPORT, dport = 6637, flags = "S", seq = 100, window = 0xffff, options = tcpopt)
#send(a)

