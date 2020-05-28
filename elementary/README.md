# Elementary: implementations of STL using pure C

- Useful to obviate the need to C++, maybe have slightly better constant
  factors.
- Assumption: maximum sizes of all data structures are known. This will obviate
  the need for resizes. So, no `<vector>`. 
- Stack: array + stack pointer.
- Queue: array + head + length.
- Priority queue: implicit heap.
- Set/Map: implicit treap.
