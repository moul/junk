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
            self.__dict__[key] = property(fget=child.__call__)

class B(object):
    def __init__(self, name, father, key, value, kind):
        self.father = father
        self.key = key
        self.value = value
        self.kind = kind
        print('  {}: inited (address={})'.format(name, self))

    def __call__(self):
        return self.value

def main():
    a = A('George')
    a.register('Bobby', B, 'key42', 42, 'method')
    a.register('Tom', B, 'key43', 43, 'property')

    print('-' * 80)
    print(dir(a))
    print(a.__dict__)
    print(a.key42)
    print(a.key42())
    print(a.key43)
    print('-' * 80)

if __name__ == "__main__":
    main()
