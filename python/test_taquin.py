from hashtable import hashtable

def taquin_expander_simple(taquin, state):
    #TODO: optimize tab copy
    base = map(int, map(str, state[0]))

    base[5], base[6] = base[6], base[5]
    yield (base, state[1] + 1)

def taquin_selector_simple(taquin, opened):
    return opened.getmin()

class taquin():
    def __init__(self, tab = None,
                 expander = taquin_expander_simple,
                 selector = taquin_selector_simple):
        self.expander = expander
        self.selector = selector
        self.success = False
        self.n = len(tab)
        self.closed = hashtable()
        self.e = (reduce(lambda x, y: x + y, tab, []), 0)
        self.opened = hashtable()
        self.opened.append(self.e)
        self.goods = 0
        for i in xrange(self.n ** 2):
            if self.e[i] == i + 1:
                self.goods += 1
            else:
                break

    def __str__(self):
        return self.state_str(self.e)

    def state_str(self, state):
        out = ''
        width = len(str(self.n ** 2))
        for i in xrange(self.n ** 2):
            print ('%-' + str(width) + 'd') % state[0][i],
            if not (i + 1) % self.n:
                print
        print "=" * (self.n * 4 - 3)
        return out

    def resolve(self):
        for step in self.resolve_iter():
            #print self
            pass

    def is_final(self, state):
        return False

    def resolve_iter(self):
        i = 0
        while i < 6:
            self.e = self.selector(self, self.opened)
            if self.is_final(self.e):
                self.success = True
                print "gagne !!!"
                print self
                return
            for state in self.expander(self, self.e):
                if state in self.opened:
                    print "%s: already in opened" % state[0]
                    pass
                elif state in self.closed:
                    print "%s: already in closed" % state[0]
                    pass
                else:
                    print "%s: not in any" % state[0]
                    self.opened.append(state)
            print self.opened
            print
            i += 1
            yield
