def f(s):
    if s == 1: return ([1], 1)
    else:
        anss = []
        for t in range(1, s):
            (trail, val) = f(s-t)
            trail.append(t)
            anss.append((trail, val+float(t)/s))

        # print(s, anss)
        anss.sort(key=lambda x:x[1], reverse=True)
        return anss[0]

for i in range(1,100):
    print("%s:%s" % (i, f(i)))

