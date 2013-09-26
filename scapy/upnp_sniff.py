#!/usr/bin/env python

from scapy.all import *

ipInput="239.255.255.250"
ip=IP()
ip.dst=str(ipInput)
udp=UDP()
udp.dport=1900
udp.sport=RandShort()

data="M-SEARCH * HTTP/1.1\r\nHost:%s:1900\r\nST:ssdp:all\r\nMan:\"ssdp:discover\"\r\n" % ipInput
send(ip/udp/data)

def monitorUPNP(pkt):
    pkt.display()
risp = sniff(filter = 'port 1900', prn = monitorUPNP)

