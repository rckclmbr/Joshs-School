#!/usr/bin/python

fac = lambda n:n-1 + abs(n-1) and fac(n-1)+n or 1L
for i in range(1, 13): print "%s\t\t%s\t\t%s" % (i, i, fac(i))
