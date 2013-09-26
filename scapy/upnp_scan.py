#!/usr/bin/env python

from scapy.all import *

ipInput="192.168.1.254"
ip=IP()
ip.dst=str(ipInput)
udp=UDP()
udp.dport=1900
udp.sport=RandShort()
data="M-SEARCH * HTTP/1.1\r\nHost:%s:1900\r\nST:upnp:rootdevice\r\nMan:\"ssdp:discover\"\r\n" % ipInput
risp = sr1(ip/udp/data, verbose=0)
risp.display()

