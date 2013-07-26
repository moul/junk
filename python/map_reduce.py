def double(n):
   # fetch from database...
   return n * 4

def my_reduce(a, b):
   print "a=%d, b=%d, a+b=%d" % (a, b, a + b)
   return a + b

a = [5, 6, 4, 2, 1]

b = map(double, a)
c = reduce(my_reduce, b)

d = reduce(my_reduce, map(double, a))

z = lambda x, y: x + y
e = reduce(z, b)

def my_toto(a, b):
   a[b] = b * 2
   return a

f = reduce(my_toto, {0: a})


print '=============='
print a
#print b
print c
print d
print e
print f

