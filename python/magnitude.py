#!/usr/bin/env python

def parseSize(text):
    prefixes = {
        'b': 1,
        'k': 1024, 'ki': 1024, 'kb': 1024,
        'm': 1024 * 1024, 'mb': 1024 * 1024,
        'g': 1024 * 1024 * 1024, 'gb': 1024 * 1024 * 1024
        }
    num = ""
    text = str(text).strip()
    while text and text[0:1].isdigit() or text[0:1] == '.':
        num += text[0]
        text = text[1:]
    num = float(num)
    letter = text.strip().lower()
    return num * (prefixes[letter] if letter in prefixes else 1)

for test in ('1024K', '1.0 K', '1.5M', '12 M', '12', '12kb', '  123.421  Kb ', '1GB', 42, '42b'):
    print test, '\r\t\t', parseSize(test)
