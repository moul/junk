#!/usr/bin/env python

import sys
import sudoku

if __name__ == "__main__":
    if len(sys.argv) > 1:
        files = [open(filename) for filename in sys.argv[1:]]
    else:
        files = [sys.stdin]
    for file in files:
        print "=" * 80
        sudoku_tab = [[int(nb) if nb > '0' and nb <= '9' else 0 for nb in line.strip()] for line in file]
        s = sudoku.sudoku(tab = sudoku_tab)
        print "=" * 80
        s.init_availables()
        s.show_amounts()
        s.show_availables()
        s.show()
        #sys.exit(1)
        print "=" * 80
        s.resolve()
        print "=" * 80
        s.show_amounts()
        s.show_availables()
        s.show()
        print "%d actions, %d routines, %d missings" % (s.actions, s.routines, s.missings)
        print "=" * 80
        del s
