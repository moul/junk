#!/usr/bin/env python

"""
path = zip(path, list(repeat({}, len(path) - 1)) + [value])                     # {} are identical objects :(
eval('%s["%s"] = %s' % ('container', '"]["'.join(map(str,path)), value))        # lol
"""

def blot(container, path, value):
    def fakeLambda(cur, obj):
        key, val = obj
        if not val == {} or not key in cur or not type(cur[key]) is dict:
            cur[key] = val
        return cur[key]

    path = map(lambda x: (x, {}), path)[:-1] + [(path[-1], value)]

    container = reduce(fakeLambda, path, container)


if __name__ == "__main__":
    from pprint import PrettyPrinter as pprint
    container = {}
    blot(container, ["a"], 42)
    blot(container, ["b"], 43)
    blot(container, ["c"], 44)
    blot(container, ["d", "e", "f", "g"], 45)
    blot(container, ["d", "e", "h"], 47)
    blot(container, ["d", "e", "i"], 48)
    blot(container, ["d", "j"], 49)
    blot(container, ["k"], 50)
    pprint(width = 1).pprint(container)

    """
    $ ./reduce_blot.py
    {'a': 42,
    'b': 43,
    'c': 44,
    'd': {'e': {'f': {'g': 45},
                'h': 47,
                'i': 48},
          'j': 49},
    'k': 50}
    """
