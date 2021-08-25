#!/usr/bin/env python3
cache = {}
INFTY = 10000000000000000

def solve_(n):
    if n <= 0: return 0
    return min(solve(n-6) + 15, solve(n-8) + 20, solve(n-10) + 25)

def solve(n):
    if n in cache:
        return cache[n]
    cache[n] = solve_(n)
    return cache[n]


def solve2(n):
    PERIOD = 120
    out = solve(n%PERIOD) + solve(PERIOD) * (n//PERIOD)
    if (n % PERIOD == 1 or n % PERIOD == 2) and (n // PERIOD >=1):
        out -= 10;
    elif (n % PERIOD == 3 or n % PERIOD == 4) and (n // PERIOD >= 1):
        out -= 5;
    return out;
        



if __name__ == "__main__":
    UPTO = 1000
    for i in range(UPTO):
        k = solve(i)
        l = solve2(i)
        if k != l:
            print("MISMATCH at %s | solve(%s) | solvefast(%s)" % (i, k, l))
            input(">")
        else:
            print("%s => %s" % (i, k))
