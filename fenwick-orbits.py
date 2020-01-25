# calculate orbits of query and update in fenwick tree

def lsb(i): return i & (-i)
def U(i): return i + lsb(i)
def Q(i): return i - lsb(i)
def orbit(f, i):
    s = set()
    while i not in s and i > 0 and i < 64:
        s.add(i); i = f(i)
    return s

if __name__ == "__main__":
    for q in range(1, 16):
        for u in range(1, 16):
            qo = orbit(Q, q); uo = orbit(U, u)
            c = qo.intersection(uo)
            print("q:%4s | u:%4s | qo: %20s | uo: %20s | qu: %4s" % 
                  (q, u, qo, uo, c))

        print("--")

