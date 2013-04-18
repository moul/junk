#!/usr/bin/env python

"""
123
  1: 123

123,456,789
  1: 123
  2: 456
  3: 789

123-129
  1: 123
  2: 124
  3: 125
  4: 126
  5: 127
  6: 128
  7: 129

123-125
  1: 123
  2: 124
  3: 125

125-123
  1: 123
  2: 124
  3: 125

125-125
  1: 125

532,421,421
  1: 532
  2: 421
  3: 421

521,123-125,123,150-152,591
  1: 521
  2: 123
  3: 124
  4: 125
  5: 123
  6: 150
  7: 151
  8: 152
  9: 591

1,2,3 4,5,6
  1: 1 4
  2: 1 5
  3: 1 6
  4: 2 4
  5: 2 5
  6: 2 6
  7: 3 4
  8: 3 5
  9: 3 6

1,2 4,5 7,8
  1: 1 4 7
  2: 1 4 8
  3: 1 5 7
  4: 1 5 8
  5: 2 4 7
  6: 2 4 8
  7: 2 5 7
  8: 2 5 8
"""

import re

def representsRangedInt(arg):
    parts = re.split('[,-]', arg)
    if len(parts) < 2:
        return False
    for part in parts:
        try:
            int(part)
        except ValueError:
            return False
    return True

def argsExpanderGenerator(baseArgs, pos = 0):
    argsCount = len(baseArgs)
    for i in xrange(pos, argsCount):
        baseArg = baseArgs[i]
        if representsRangedInt(baseArg):
            left =  baseArgs[:i]
            right = baseArgs[i+1:]
            if baseArg.find(',') > -1:
                for solution in baseArg.split(','):
                    for child in argsExpanderGenerator(left + [solution] + right):
                        yield child
                return
            if baseArg.find('-') > -1:
                (a, b) = map(int, baseArg.split('-'))
                m = min(a, b)
                M = max(a, b)
                for x in xrange(m, M + 1):
                    for child in argsExpanderGenerator(left + [str(x)] + right):
                        yield child
                return
            return
        else:
            for child in argsExpanderGenerator(baseArgs, pos + 1):
                yield child
            return
        return
    yield baseArgs


if __name__ == "__main__":
    for test in [
        ['123'],
        ['123,456,789'],
        ['123-129'],
        ['123-125'],
        ['125-123'],
        ['125-125'],
        ['532,421,421'],
        ['521,123-125,123,150-152,591'],
        ['1,2,3', '4,5,6'],
        ['1,2', '4,5', '7,8'],
        ]:
        print ' '.join(test)
        i = 1
        for solution in argsExpanderGenerator(test):
            print "  %d: %s" % (i, ' '.join(solution))
            i += 1
        print
