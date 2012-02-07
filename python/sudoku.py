#SUM_LINE = 45
#SUM_TOTAL = SUM_LINE * 9

class sudoku():
    def __init__(self, tab = None, availables = None, debug = 0):
        self.actions = 0
        self.tab = tab
        self.sum = sum([sum(line) for line in tab])
        self.availables = availables
        self.debug = debug
        self.routines = 0
        self.missings = 81 - sum([sum([tab[i][j] > 0 and 1 or 0 for i in xrange(9)]) for j in xrange(9)])
        self.amounts = {}
        self.amounts['horizontal'] = [{1:9,2:9,3:9,4:9,5:9,6:9,7:9,8:9,9:9} for i in xrange(9)]
        self.amounts['vertical'] = [{1:9,2:9,3:9,4:9,5:9,6:9,7:9,8:9,9:9} for i in xrange(9)]
        #self.amounts['regions'] = [{1:9,2:9,3:9,4:9,5:9,6:9,7:9,8:9,9:9} for i in xrange(9)]

    def __str__(self):
        tab_str = '\n'.join([''.join([str(chr) if chr > 0 else ' ' for chr in line]) for line in self.tab])
        return tab_str

    def show_availables(self):
        line_number = 0
        print "--------------------------------+" * 3
        for line in self.availables:
            if line_number > 1 and line_number % 3 == 0:
                print "-" * 98
            col_number = 0
            for col in line:
                b = col_number == 0 and '|' or ''
                c = col_number > 1 and (col_number + 1) % 3 == 0 and '|' or ' '
                s = ''.join(map(str, col))
                if not len(s):
                    s = '.'
                print '%s%9s%s' % (b, s, c),
                col_number += 1
            print
            line_number += 1
        print "-" * 98

    def show(self):
        i = 0
        for line in self.__str__().split('\n'):
            if i > 0 and i % 3 == 0:
                print '---+---+---'
            print line[0:3] + '|' + line[3:6] + '|' + line[6:9]
#            + ' ' + str(sum(map(int, list(line))))
            i += 1

    def show_amounts(self):
        """
1xxx xxx xxx
2xxx xxx xxx
3xxx xxx xxx
4xxx xxx xxx
5xxx xxx xxx
6xxx xxx xxx
7xxx xxx xxx
8xxx xxx xxx
9xxx xxx xxx
 ---+---+--- 123456789
|123|123|123|xxxxxxxxx
|456|456|456|xxxxxxxxx
|789|789|789|xxxxxxxxx
 ---+---+---
|123|123|123|xxxxxxxxx
|456|456|456|xxxxxxxxx
|789|789|789|xxxxxxxxx
 ---+---+---
|123|123|123|xxxxxxxxx
|456|456|456|xxxxxxxxx
|789|789|789|xxxxxxxxx
 ---+---+---
"""
#        for key in self.amounts:
#            print "=== %s === " % key
#            for line in self.amounts[key]:
#                print line
#            #print self.amounts[key]
#        print
        for i in xrange(9):
            #print self.amounts['vertical'][i]
            print "%d: %s %s" % (i + 1,
                                 ''.join([str(self.amounts['vertical'][c][i + 1]) + (not (c + 1) % 3 and ' ' or '') for c in xrange(9)]),
                                 (i == 8 and ' 123456789' or ''))
        for i in xrange(9):
            if not i % 3:
                print "   ---+---+---"
            #print ['x'] * 9 + [''.join([str(self.amounts['horizontal'][i][c]) for c in self.amounts['vertical'][i]])]
            a = {}
            a[0] = '   '
            a[1] = '   '
            a[2] = '   '
            d = ''.join([str(self.amounts['horizontal'][i][x]) for x in self.amounts['horizontal'][i]])
            print "  |%s|%s|%s|  %s" % (a[0], a[2], a[2], d)
        print "   ---+---+---"



    def resolve(self):
        list(self.resolve_iter())

    def init_availables(self):
        self.availables = [[{1:1,2:2,3:3,4:4,5:5,6:6,7:7,8:8,9:9} for i in xrange(9)] for j in xrange(9)]
        for y in xrange(9):
            for x in xrange(9):
                if self.tab[y][x]:
                    self._update_availables(y, x)
                    self.sum += self.tab[y][x]
        #self.show_availables()

    def _update_availables(self, y, x):
        nb = self.tab[y][x]
        #print 'f', nb, self.availables[4][3]
        for i in self.availables[y][x]:
            self.amounts['horizontal'][y][i] -= 1
            self.amounts['vertical'][x][i] -= 1
        self.availables[y][x] = {}
        self.amounts['horizontal'][y][nb] = 0
        self.amounts['vertical'][x][nb] = 0
        for i in xrange(9):
            if nb in self.availables[y][i]:
                del self.availables[y][i][nb]
                self.amounts['vertical'][i][nb] -= 1
                #self.amounts['horizontal'][y][nb] -= 1
            if nb in self.availables[i][x]:
                del self.availables[i][x][nb]
                #self.amounts['vertical'][x][nb] -= 1
                self.amounts['horizontal'][i][nb] -= 1
        m = int(x / 3) * 3
        n = int(y / 3) * 3
        #print x, y, m, n, self.tab[y][x]
        for i in xrange(m, m + 3):
            for j in xrange(n, n + 3):
                if nb in self.availables[j][i]:
                    del self.availables[j][i][nb]
                    self.amounts['vertical'][i][nb] -= 1
                    self.amounts['horizontal'][j][nb] -= 1
        #print 'e', nb, self.availables[4][3]

    def _resolve_iter_horizontal(self):
        for y in xrange(9):
            for x in xrange(8):
                if len(self.availables[y][x]) == 2:
                    for x2 in xrange(x + 1, 9):
                        if self.availables[y][x] == self.availables[y][x2]:
                            for x3 in xrange(9):
                                if x3 != x and x3 != x2:
                                    for nb in self.availables[y][x]:
                                        if nb in self.availables[y][x3]:
                                            #print 'c', y2, x, nb, self.availables[4][3]
                                            del self.availables[y][x3][nb]
                                            self.amounts['horizontal'][y][nb] -= 1
                                            self.amounts['vertical'][x3][nb] -= 1
                                            self.actions += 1

    def _resolve_iter_vertical(self):
        for x in xrange(9):
            for y in xrange(8):
                if len(self.availables[y][x]) == 2:
                    for y2 in xrange(y + 1, 9):
                        if self.availables[y][x] == self.availables[y2][x]:
                            for y3 in xrange(9):
                                if y3 != y and y3 != y2:
                                    for nb in self.availables[y][x]:
                                        if nb in self.availables[y3][x]:
                                            #print 'b', y3, x, nb, self.availables[4][3]
                                            del self.availables[y3][x][nb]
                                            self.amounts['horizontal'][y3][nb] -= 1
                                            self.amounts['vertical'][x][nb] -= 1
                                            self.actions += 1


    def _resolve_iter_regions(self):
        for n in xrange(0, 9, 3):
            for m in xrange(0, 9, 3):
                for a in xrange(9):
                    x = int(a / 3)
                    y = a % 3
                    if len(self.availables[n + y][m + x]) == 2:
                        for a2 in xrange(a + 1, 9):
                            x2 = int(a2 / 3)
                            y2 = a2 % 3
                            if self.availables[n + y][m + x] == self.availables[n + y2][m + x2]:
                                for a3 in xrange(9):
                                    if a3 != a2 and a3 != a:
                                        x3 = int(a3 / 3)
                                        y3 = a3 % 3
                                        #print n, y, m, x, n + y, m + x, len(self.availables), len(self.availables[n + y])
                                        #self.show_availables()
                                        for nb in self.availables[n + y][m + x]:
                                            if nb in self.availables[n + y3][m + x3]:
                                                #print n + y3, m + y3, nb
                                                #print 'a', n + y3, m + x3, nb, self.availables[4][3]
                                                del self.availables[n + y3][m + x3][nb]
                                                self.amounts['horizontal'][n + y3][nb] -= 1
                                                self.amounts['vertical'][m + x3][nb] -= 1
                                                self.actions += 1
                                                pass

    def _resolve_inline_or_alone_in_region(self):
        rev_range = {0: range(0, 0) + range(3, 9),
                     3: range(0, 3) + range(6, 9),
                     6: range(0, 6) + range(9, 9)}
        for n in xrange(0, 9, 3):
            for m in xrange(0, 9, 3):
                for nb in xrange(1, 10):
                    res = {'n': n,
                           'm': m,
                           'nb': nb,
                           'count': {'rows': 0,
                                     'lines': 0},
                           'last': {}}
                    for i in xrange(3):
                        if int(nb in self.availables[n + i][m + 0]) \
                                + int(nb in self.availables[n + i][m + 1]) \
                                + int(nb in self.availables[n + i][m + 2]):
                            res['count']['rows'] += 1
                            res['last']['rows'] = i
                        if int(nb in self.availables[n + 0][m + i]) \
                                + int(nb in self.availables[n + 1][m + i]) \
                                + int(nb in self.availables[n + 2][m + i]):
                            res['count']['lines'] += 1
                            res['last']['lines'] = i
                    if res['count']['lines'] == 1:
                        for z in rev_range[n]:
                            if nb in self.availables[z][m + res['last']['lines']]:
                                del self.availables[z][m + res['last']['lines']][nb]
                    if res['count']['rows'] == 1:
                        for z in rev_range[m]:
                            if nb in self.availables[n + res['last']['rows']][z]:
                                del self.availables[n + res['last']['rows']][z][nb]
        print

    def backtrack(self):
        print ' *** backtrack *** '
        pass

    def resolve_iter(self):
        if not self.availables:
            self.init_availables()
        changed = -1
        while changed != self.actions:
            self.routines += 1
            changed = self.actions

            # resolve
            for y in xrange(9):
                for x in xrange(9):
                    if len(self.availables[y][x]) == 1:
                        #print y, x, self.availables[y][x]
                        self.tab[y][x] = sum(self.availables[y][x])
                        self.sum += self.tab[y][x]
                        self._update_availables(y, x)
                        self.actions += 1
                        self.missings -= 1
                        yield

            self._resolve_iter_horizontal()
            self._resolve_iter_vertical()
            self._resolve_iter_regions()
            self._resolve_inline_or_alone_in_region()

            for i in xrange(9):
                for nb in xrange(1, 10):
                    if self.amounts['horizontal'][i][nb] == 1:
                        #print "horizontal: y = %d, nb = %d" % (i, nb)
                        for x in xrange(9):
                            if nb in self.availables[i][x]:
                                #print y, x, self.availables[i][x]
                                self.tab[i][x] = nb
                                self.sum += nb
                                self._update_availables(i, x)
                                self.actions += 1
                                self.missings -= 1
                                yield
                                break
                    if self.amounts['vertical'][i][nb] == 1:
                        #print "vertical: x = %d, nb = %d" % (i, nb)
                        for y in xrange(9):
                            if nb in self.availables[y][i]:
                                #print y, x, self.availables[y][i]
                                self.tab[y][i] = nb
                                self.sum += nb
                                self._update_availables(y, i)
                                self.actions += 1
                                self.missings -= 1
                                yield
                                break
        self.backtrack()
