#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define K 100001
#define NMAX 200001
#define INF 1e7
using I = long long int;
using namespace std;
I N, D, A;

struct S { I xalive; I hp; S() : xalive(INF), hp(0) {}; S(I xalive, I hp) : xalive(xalive), hp(hp) {} };
S join(S a, S b) { if (a.xalive < b.xalive) { return a; } else { return b; } }
S xh[NMAX];
S tree[2*NMAX]; // (location, hp)
void dbgprint(int nl, int nr, int stix) {
    if (nl == nr) { cout << "dbg " << "tree[" << stix <<"] := (" 
        << nl <<")"  << " |xalive: " << tree[stix].xalive << "|hp:" << tree[stix].hp <<  "\n";  return;
    }
    int mid = (nl + nr) / 2;
    dbgprint(nl, mid, stix*2);
    dbgprint(mid+1, nr, stix*2+1);
}
S qlalive(int ql, int qr, int nl, int nr, int stix) {
    if (qr < nl || nr < ql) { return S(); }
    if (ql <= nl && nr <= qr) { return tree[stix]; }
    int mid = (nl + nr) / 2;
    return join(qlalive(ql, qr, nl, mid, stix*2), qlalive(ql, qr, mid+1, nr, stix*2+1));
}

// apply damage
void damage(int d, int ql, int qr, int nl, int nr, int stix) {
    cout << "damage(" << d << ") [" << ql << "," << qr << "] [" << nl << "|" << stix << "|" << nr << "]\n";
    if (qr < nl || nr < ql) { return; }
    if (nl == nr) { 
        tree[stix].hp = max<I>(tree[stix].hp-d, 0); 
        tree[stix].xalive = tree[stix].hp > 0 ? tree[stix].xalive : INF;
        return;
    }
    int mid = (nl + nr) / 2;
    damage(d, ql, qr, nl, mid, stix*2);
    damage(d, ql, qr, mid+1, nr, stix*2+1);
    tree[stix] = join(tree[stix*2], tree[stix*2+1]);
}
void build(int nl, int nr, int stix) {
    cout << "build [" << nl << "|" << stix << "|" << nr << "]\n";
    if (nl == nr) { tree[stix] = xh[nl]; return; }
    int mid = (nl + nr) / 2;
    build(nl, mid, stix*2);
    build(mid+1, nr, stix*2+1);
    tree[stix] = join(tree[stix*2], tree[stix*2+1]);
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> D >> A;
    for(int i = 1; i <= N; ++ i) { int x, h;  cin >> x >> h; xh[i] = S(x, h); };
    build(1, N, 1);
    // sort by X coordinate
    // std::sort(xh, xh+N, [](II xh1, II xh2) { return xh1.first < xh2.first; });
    int nturn = 0;
    S s;
    while ((s = qlalive(1, N, 1, N, 1)).xalive != INF) {
        // drop these many bombs
        int nbomb = (s.hp+A-1)/A;
        nturn += nbomb;
        int dmg = nbomb * A;
        dbgprint(1, N, 1);
        cout << "s.hp: " << s.hp << " |s.x: " << s.xalive << "|nbomb: " << nbomb << "|dmg: " << dmg << "\n" <<flush; char c; cin>>c;
        // apply that much damage to everyone
        damage(dmg, s.xalive, s.xalive+2*D, 1, N, 1);
    }
}
