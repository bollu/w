# CSCS problems and solutions

To find problems that are solved in multiple ways, look for `namespace`. Often
the first implementation `f0 { ... }` will be the naive solution, while `f1 { ... }`
will use some neat abstract algebra or a more insightful technique.


- [Consider solving USACO next](https://usaco.guide/)
- [Super awesome notebook](https://github.com/koosaga/olympiad/blob/master/Library/teamnote.pdf)



## Unsolved problems
- [Nearest smaller values](https://cses.fi/problemset/task/1645)
- [Increasing subsequence](https://cses.fi/problemset/task/1145) needs segtree.

## Unsolved correctness proofs
- [Playlist](https://cses.fi/problemset/task/1141) Have handwavy proof.
- [Towers](https://cses.fi/problemset/task/1073)
- [Tasks and deadlines](https://cses.fi/problemset/task/1630/) 
  Have hand wavy calculus proof, need to check that its correct.
- [Book shop](https://cses.fi/problemset/task/1158/) and 
  [Coin combinations II](https://cses.fi/problemset/task/1636). What structure
  of the problem are we able to exploit to make it 'monotonic-like'?
- [Rectangle cutting](https://cses.fi/problemset/task/1744/): why do we need to loop
  over both width and height?
- Money sums: write non cheese actual DP solution.
- [Two Sets II](https://cses.fi/problemset/task/1093/): I don't understand the boundary conditions well

## Unsolved with resrictions
- [Ferris wheel](https://cses.fi/problemset/task/1090): find matroid
- [Concert Tickets](https://cses.fi/problemset/task/1091). I use `multiset`. Implement
  your own!
- [Sliding window](https://cses.fi/problemset/task/1076/). I cheesed and used policy
  based data structures. Implement your own!
- Counting rooms: solve using DSU.

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

#### [Building teams](https://cses.fi/problemset/task/1668/)

- Bipartite <-> 2 colorable <-> no odd length cycle.
- Check bipartition => cycles of even length
- [CP algorithms page on checking if graph is bipartite](https://cp-algorithms.com/graph/bipartite-check.html)
- Why does BFS work for 2 bipartite?

- **If algo works => graph is bipartite**: Assume run BFS, color each layer 
  with an alternate color, and when we finally check edges, we get that each edge
  connects vertices with different colors. Then we clearly have a valid 2 coloring
  (by definition) and the graph is bipartite.
  
- **graph is bipartite => algo will work**: Say we start with a node in part A 
  of the graph. All of its neighbours will be in part B of the graph, which will receive
  the other color. The neighbours of part B (at distance 3 from the start node) will be
  at part A, and so on. Perform induction on path length.
 
- [Notes from McGill uni that goes through the same](https://www.cs.mcgill.ca/~pnguyen/360W11/a1sol.pdf)

#### [Monsters: multi source BFS](https://cses.fi/problemset/task/1194)

TIL "multi source BFS". It's fairly intuitive, we can imagine that we create a fake
source node connected to all our "real sources"
and start running BFS from this node. If we did this, then in one iteration
of the algorithm, the queue would have been filled with the "real sources". So we might
as well just start our BFS from the "real sources". This line of thought makes the
correctness proof feel easier to me.



- **Correctness, part 1**: if the monster can reach the
  escape node before you, there's no way you can escape using this route.

- **Correctness, part 2**: if you can reach an escape node before the monsters, then
   we can escape through this path *if* we can reach it in time, because the monsters
   cannot reach it in time.

## Food for thought

#### Unsolved problem: Line of Wines

- [Question from errichto](https://www.youtube.com/watch?v=pwpOC1dph6U&list=PLl0KD3g-oDOHpWRyyGBUJ9jmul0lUOD80&index=6)

#### Intuition for coin change

- [Errichto youtube video](https://www.youtube.com/watch?v=1mtvm2ubHCY&list=PLl0KD3g-oDOHpWRyyGBUJ9jmul0lUOD80&index=5)
If we had coins `{1, 2, 3}` we want to only count say `1 + 2 + 3`, not `2 + 1 + 3` and  `3 + 1 + 2` and so on,
so the order does not matter.  

We encode this by canonicalizing into the lex smallest order. So we pick the representative `[1, 1, 2]`.
This allows us to reduce the dp state to `(sum, max coin used so far)` since we have reduced the
state space to lex ordered coin sequences. This is what gives us the state space reduction.




#### Variable naming convention for updated variable

```cpp
// STYLISTIC CHOICE: repeat letter for new version.
coord cc = { c.first+delta[i].first, c.second + delta[i].second};
```

Use variable name `cc` for the new version of `c`. Works in general to repeat
the letter, instead of using `c'` as we would in Haskell.

#### Representing directions in grids

```cpp
// ESWN [clockwise from east.
const coord delta[4] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1}};
```

This allows us to find the opposite direction with `(i+2)%2`. Very neat. Plus I'm
sure that storing in consistent clockwise order will come in handy for more things.

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




