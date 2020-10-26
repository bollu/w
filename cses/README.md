# CSCS problems and solutions

To find problems that are solved in multiple ways, look for `namespace`. Often
the first implementation `f0 { ... }` will be the naive solution, while `f1 { ... }`
will use some neat abstract algebra or a more insightful technique.

- [Consider solving USACO next](https://usaco.guide/)



## Unsolved problems
- [Nearest smaller values](https://cses.fi/problemset/task/1645)

## Unsolved correctness proofs
- [Playlist](https://cses.fi/problemset/task/1141) Have handwavy proof.
- [Towers](https://cses.fi/problemset/task/1073)
- [Tasks and deadlines](https://cses.fi/problemset/task/1630/) 
  Have hand wavy calculus proof, need to check that its correct.

## Unsolved with resrictions
- [Ferris wheel](https://cses.fi/problemset/task/1090): find matroid
- [Concert Tickets](https://cses.fi/problemset/task/1091). I use `multiset`. Implement
  your own!
- [Sliding window](https://cses.fi/problemset/task/1076/). I cheesed and used policy
  based data structures. Implement your own!


## Solved correctness proofs


# [Factory machines](https://cses.fi/problemset/task/1620)

Use monotonicity of "number of widgets made in a given amount of time"
to find the minimum time where we make X number of widgets.

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

  
#### [Towers](https://cses.fi/problemset/task/1073)

- Greedily choose to place blocks on top of current towers.
- Assume optimal choice of whether to place on top of current tower or create a new tower is `O*`.
- Assume greedy choice solution is `O`.
- If the `O` and `O*` agree on the first choice, recurse.
- If `O` and `O*` do not agree, analyze the situation as follows:
- Let us build a tower `<T1>:<cur-block>`
- Let the `O*` solution build a tower `<T1*>:<cur-block>` or `<cur-block>`, where `<T1*> /= <T1>`.
- `(A1)` In this case, we have that `T1 > cur-block` and `T1* > cur-block`.
  For the optimal solution, move the blocks on top of `T1*` to be on top of `T1`.
- **TODO**



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


#### Poset problems

- Longest increasing subsequence: longest chain in poset of `(ix, value)`
- Activity scheduling: longest chain in interval poset. Periods of activity is interval
- Max overlapping intervals: longest chain in subset poset: `(l1, r1) <= (l2, r2)` if `l1 <= l2 <= r2 <= r1`
  [ie, first subset contains the second]
- Knowing a data structure for poset maintainance seems invaluable!

#### Nice binary search problems

- sum of three values
- factory machines

#### Interesting idea to refactor two pointers

- Look at `subarray_sums_{1, 2}.cpp` where we use a `map` to check whether a 
  'back pointer' has computed some information that we need to satisfy the
  predicate.
