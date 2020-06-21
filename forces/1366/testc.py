#!/usr/bin/env python3
def bitsoncount(x):
    return bin(x).count('1')


def count(n):
    xs = list(range(0, n+1))
    count = 0
    for i in range(n):
        count += bitsoncount(xs[i] ^ xs[i+1])
    return count

if __name__ == "__main__":
    for i in range(1, 20):
        print("%s: %s" % (i, count(i)))

