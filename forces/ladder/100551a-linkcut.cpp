// https://cp-algorithms.com/data_structures/deleting_in_log_n.html
#include <assert.h>
#include <iostream>
#include <fstream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<functional>
#include<utility>
#include<tuple>
#include<map>


// switch-preferred-child(x, y):
// -----------------------------
// path-parent(right(x)) = x
// right(x, y)


// Access(v):
// ---------
// Switch-Path-Parent(v, null)
// while (v is not root)
//   w = path-parent(v)
//   splay(w)
//   Switch-Path-Parent(w, v)
//   path-parent(v) = null
//   v = w
// splay(v)

// Link(v, w):
// -----------
// Access(v)
// Access(w)
// left(v) = w

// Cut(v):
// -------
// Access(v)
// left(v) = null


