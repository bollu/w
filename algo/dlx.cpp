// https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf
#include <iostream>
using namespace std;

// dlx nodes.
// REMOVE:
// x->r->l = x->l; 
// x->l->r = x->r;
//
//
// ADDBACK:
// x->r->l = x;
// x->l->r = x;
//
// Can we pick a set of rows, that have *exactly* one # in each column?
//        c1  c2  c3  c4  c5  c6 c7
// r1: (  -   -   #   -   #   #  - )
// r2: (  #   -   -   #   -   -  # )
// r3: (  -   #   #   -   -   #  - )
// r4: (  #   -   -   #   -   -  - )
// r5: (  -   #   -   -   -   -  # )
// r6: (  -   -   -   #   #   -  # )
//
// Yes!
//
// we can, we can pick:
//    - { r3,          r4,       r5 } which overlap with columns as
//    - {{c3, c5, c6}, {c1, c4}, {c2, c7}}.
//    - Each column is overlapped with exactly once.
//
// alternatively, we can think of rows as elements, columns as subsets.
// Then we have to find a some rows(elements) such that each column (subset)
// is intersected exactly once.
//
//   r3 -> collides with {c3, c5, c6}
//   r4 -> collides with {c1, c4}
//   r5 -> collides with {c2, c7}
//
// Algorithm X
// ------------
// 1. If A is empty, the problem is solved; terminate successfully.
// 2. Otherwise choose a column, c (deterministically).
// 3. Choose a row, r, such that A[r, c] = 1 (nondeterministically).
// 4. Include r in the partial solution.
// 5. For each j such that A[r, j] = 1:
// 6.     delete column j from matrix A;
//   
// 7.     for each i such that A[i, j] = 1:
// 8.         delete row i from matrix A.
// 9. Repeat this algorithm recursively on the reduced matrix A
static const int N = 100;

int rs[N];
int cs[N];
int D[N];
int U[N];
int L[N];
int R[N];
int C[N];
int S[N];
int os[N];
int h;
static const int INFTY = 10000;

int choose_col() {
    int c = -1; int s = INFTY;
    for(int j = R[h]; j != h; j = R[j]) { if (S[j] < s) { c = j; s = S[j]; } }
    return c;
}

void cover_col(const int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for(int i = D[c]; i != c; i = D[i]) { 
        for(int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j]; D[U[j]] = D[j];
            S[C[j]] -= 1;
        }
    }
}


void uncover_col(const int c) {
    // if we had janus, this would be *automatic*
    // janus for backtracking.
    for(int i = U[c]; i != c; i = U[i]) {
        for(int j = L[i]; j != i; j = L[j]) {
            S[C[j]] += 1;
            U[D[j]] = j;
            D[U[j]] = j;
        }
    }
    L[R[c]] = c; R[L[c]] = c;
}

void printsoln(const int k) {
    for(int i = 0; i < k; ++i) {
        cout << i << "i: " << os[i];
        return;
    }
}

bool search(int k) {
    if(R[h] == h) {
        printsoln(k); return true;
    }
    const int c = choose_col();
    cover_col(c);
    bool success = false;
    for(int r = D[c]; r != c; r = D[r]) {
        os[k] = r;
        for(int j = R[r]; j != r; r = R[j]) { cover_col(j); }
        success = search(k+1);
        // r = os[k]; // what?
        // c = C[r]; ?? what?
        for(int j = L[r]; j != r; j = L[j]) { uncover_col(j); }
        if (success) break;
    }
    uncover_col(c);
    return success;
}

int main() {

}
