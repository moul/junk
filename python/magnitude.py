#!/usr/bin/env python

def parseSize(text):
    prefixes = {
        'K': 1024,
        'M': 1024 * 1024,
        'G': 1024 * 1024 * 1024
        }
    num = ""
    while text and text[0:1].isdigit() or text[0:1] == '.':
        num += text[0]
        text = text[1:]
    num = float(num)
    letter = text.strip()
    return num * (prefixes[letter] if letter in prefixes else 1)

for test in ('1024K', '1K', '1.5M', '12M', '12', '12K'):
    print test, parseSize(test)
