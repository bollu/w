#!/usr/bin/env python3

N = 20
M = 10

def mex(xs):
    xsset = set(xs)
    i = 0
    while True:
        if i in xsset:
            i += 1
            continue
        return i

def log2(x):
    if x == 1:
        return 0
    if x == 2:
        return 1
    return log2(x//2)

def ispow2(x):
    if x == 1:
        return True
    if x % 2 == 1:
        return False
    return ispow2(x//2)

def pow2(k):
    if k == 0:
        return 1
    if k == 1:
        return 2
    p = pow2(k//2)
    if k % 2 == 0:
        return p*p
    else:
        return p*p*2

def nextpot(n):
    if n == 1:
        return 2
    if ispow2(n):
        return n
    else:
        return pow2(log2(n)+2)

def smallest_pot_divides(m):
    for i in range(log2(m)+2, -1, -1):
        if m % pow2(i) == 0:
            return pow2(i)
def ans(n, m):
 if (m == 0): return 0
 if (m == 1): return 1 if n == 0 else 0
 k = smallest_pot_divides(m)
 return max(0, m - (n // k) * k)

for i in range(N):
    xs = [i^j for j in range(M)]
    ys = [(k, mex(xs[0:k])) for k in range(M+1)]
    zs = [(k, ans(i, k)) for k in range(M+1)]
    print("i: %s\n\t| vals: %s\n\t| mexs: %s\n\t| anss: %s\n\t| eq: %s" % (i, list(enumerate(xs)), ys, zs, ys == zs))
    # print("i: %s\n\t| vals: %s\n\t| mexs: %s\n"% (i, list(enumerate(xs)), ys))
        
