# CSCS problems and solutions

To find problems that are solved in multiple ways, look for `namespace`. Often
the first implementation `f0 { ... }` will be the naive solution, while `f1 { ... }`
will use some neat abstract algebra or a more insightful technique.

## Unsolved Correctness proofs 


## Unsolved problems
- [Movie Festival](https://cses.fi/problemset/task/1629)

## Unsolved without STL

- [Concert Tickets](https://cses.fi/problemset/task/1091). I use `multiset`. Implement
  your own!

## Solved correctness proofs

#### [Ferris wheel](https://cses.fi/problemset/task/1090)

- Consider the smallest child with weight `s`.
- Consider the largest child, `b(s)` such that `s + b(s) <= 12` [I write `b(s)` to show that `b` is a parameter of `s`]
- If the optimal solution paired `s` with `b(s)` we are done.
- Assume not, that the optimal solution paired `s` with `w`. So we have `s + w <= 12`
- Then say that in the optimal optimal  `b(s)` was paired with `c`. So we have `b(s) + c <= 12`.
- Since we have that `b(s)` is the largest thing that can be paired with `s`, we have that 
  `w <= b(s)` since `w` was also paired with `s`.
- Thus since `b(s) + c <= 12 /\ w <= b(s)` we have that `w + c <= 12`.
- Thus, we can "swap" the pairs to create the pairs `(s, b(s))` and `(w, c)`.
- We didn't deal with the cases where stuff is not paired, but we can repair
  the proof to cover those cases.
- The key idea is the swap based exchange argument.

