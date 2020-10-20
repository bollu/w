# CSCS problems and solutions

To find problems that are solved in multiple ways, look for `namespace`. Often
the first implementation `f0 { ... }` will be the naive solution, while `f1 { ... }`
will use some neat abstract algebra or a more insightful technique.



## Unsolved problems
- [Movie Festival](https://cses.fi/problemset/task/1629)

## Unsolved correctness proofs
- [Playlist](https://cses.fi/problemset/result/1157099/)
- [Playlist](https://cses.fi/problemset/result/1157099/): think about relation to
  max sum subarray.

## Unsolved with resrictions
- [Ferris wheel](https://cses.fi/problemset/task/1090): find matroid
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

#### [Playlist](https://cses.fi/problemset/task/1141)

- Solution 0: use two pointers. Keep a set of elements that we have senen before,
  and use that to two pointers.
- Solution 1: Borrow the idea from parallel/fold based maximum sum subarray.
  Keep for every element `xs[i]` an index `chopoff[xs[i]]` that tells us what
  the last occurence of `xs[i]` was. This way, the "length of valid subsequence ending at i"
  becomes `i - max(j < i) { chopoff[j] }`. That is, we end at `i`, and we try to
  take the longest legal segment that we can. So we chop off at the _previous_
  occurence of `j`.

- This is inspired by max sum subarray, where we also perform
  `best_sum = sum[i] - min(j < i) { sum[j] }`.

- So we keep track of a "height" of where we are (`sum[i]` / `i`), and we keep
  track of a "baseline" (`min (j < i) { sum[j] }` / `max(j < i) chopoff[j]`).

- I wonder if every two pointer algorithm can be viewed in terms of this
  "mountain peak - baseline" style solution.

#### Intuition for `lower_bound`, `upper_bound`:

- you get the range of values equal to `x` as `[lower_bound(k), upper_bound(k))`
- similar to the array range, which is `[0, n)`
- basically they represent the left-most and right-most iterators **before which**
  we can insert the key `k`.

```
        | lower, upper bound
        | v
        | v
< < < _ | > > >
      ^
      ^
      safe to insert element here [BEFORE]
```

- Think about inserting an element at that point and pushing everything else to
  the right. So to "make room", we push to the right.

- Alternatively, think that our iterators are always `-ε`. This works, since the
  pictures will look like this:

- Case with some elements equal to key:

```
      | lower     |upper
      | bound     |bound
      | v         |v
< < < | ε = = = = |ε  > > > > >
        [----------]
        inteval of equal elements
```
- Case with no elements equal to key:

```
      lower, upper bound  
      v |                  
      v |                  
< < < ε | > > >
      ^
      ^
      safe to insert element here [BEFORE]
```
