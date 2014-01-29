class A(object):
    children = []

    def __init__(self, name):
        self.name = name
        print('{}: inited (address={})'.format(self.name, self))

    def register(self, child_name, cls, key, value, kind):
        child = cls(child_name, self, key, value, kind)
        print('{}: registering child: {}'.format(self.name, child))
        self.children.append(child)
        if kind == 'method':
            self.__dict__[key] = child.__call__
        elif kind == 'property':
            #setattr(self, key, property(fget=child.__call__))
            #self.__dict__[key] = property(fget=child.__call__)
            #setattr(self.__class__, key, property(fget=child.__call__))
            setattr(self.__class__, key, property(fget=child.prop))


class B(object):
    def __init__(self, name, father, key, value, kind):
        self.father = father
        self.key = key
        self.value = value
        self.kind = kind
        print('  {}: inited (address={})'.format(name, self))

    def prop(self, *args):
        return self.__call__()

    def __call__(self, *args):
        return [self.value] + list(args)


def print_a(a):
    print('-' * 80)
    print(a.name)
    print('  dir:  {}'.format([key for key in dir(a) if key[0] != '_']))
    print('  dict: {}'.format(a.__dict__))
    for key in ['key42', 'key43', 'key44', 'key45']:
        try:
            print('    {}={}'.format(key, getattr(a, key)))
            try:
                print('    {}()={}'.format(key, getattr(a, key)()))
            except:
                print('    {}() raised'.format(key))
        except:
            print('    {} raised'.format(key))
        print('')
    print('-' * 80)
    print('\n' * 2)


def main():
    a = A('George')
    a.register('Bobby', B, 'key42', 42, 'method')
    a.register('Tom', B, 'key43', 43, 'property')
    print_a(a)

    c = A('Alain')
    c.register('Tiffany', B, 'key44', 44, 'method')
    c.register('Barney', B, 'key45', 45, 'property')
    print_a(c)


if __name__ == "__main__":
    main()
