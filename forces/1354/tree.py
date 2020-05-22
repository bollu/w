import math

def binstr(maxn, n):
    nbits = math.ceil(math.log(maxn, 2))
    bits = [1 if n & (1 << i) else 0 for i in range(0, nbits)]
    bits = bits[::-1]
    return "".join([str(b) for b in bits])

def tree_closed_open(tree_len, ix, l, length, depth):
    marker = ""
    if ix >= tree_len: marker = "*"

    print(" "*depth + "[%d---(%d:%s)--%d) %s" % (l, ix, binstr(1+tree_len, ix), l + length, marker))
    if ix >= tree_len:
        pass
    else:
        halflen = length//2
        r = l + length
        tree_closed_open(tree_len, ix*2, l, halflen, depth+1)
        tree_closed_open(tree_len, ix*2+1, l+halflen, length-halflen, depth+1)

def treestart_closed_open(tree_len):
    return tree_closed_open(tree_len, 1, 1, tree_len, 0)

def tree_closed_closed(tree_len, ix, l, r, depth):
    marker = ""
    if l == r: marker = "*"

    print(" " * depth + "[%d---(%d:%s)---%d] %s" % (l, ix, binstr(1+tree_len, ix), r, marker))
    if l == r: pass
    else:
        mid = (l+r)//2
        tree_closed_closed(tree_len, ix*2, l, mid, depth+1)
        tree_closed_closed(tree_len, ix*2+1, mid+1, r, depth+1)


def treestart_closed_closed(tree_len):
    return tree_closed_closed(tree_len, 1, 1, tree_len, 0)

if __name__ == "__main__":
    print("closed open:")
    treestart_closed_open(9)
    print("closed closed:")
    treestart_closed_closed(9)
