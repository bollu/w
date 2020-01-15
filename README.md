# Algorithms collection

All of these are written in Whitney style C++ as an exercise to learn his dense
programming style. As I understand, the argument for this style is that it
enables one to rapidly scan code. Since no scrolling is needed (all code fits
on a page), and variable names are very succinct (single letter or two letter),
it enables a high degree of cohesion when it comes to understanding code.

This sample screenshot of the famous
[Incunabulum essay in `J`](https://code.jsoftware.com/wiki/Essays/Incunabulum).
To quote the essay:

> One summer weekend in 1989, Arthur Whitney visited Ken Iverson at Kiln Farm
> and produced—on one page and in one afternoon—an interpreter fragment on the
> AT&T 3B1 computer. I studied this interpreter for about a week for its
> organization and programming style; and on Sunday, August 27, 1989, at about
> four o'clock in the afternoon, wrote the first line of code that became the
> implementation described in this document. Arthur's one-page interpreter
> fragment is as follows:

![Sample screenshot of how I view the code](screenshot-incunabulum.png)

#### Code written in this style of common algorithms

- [`euc.cpp` - extended euclidian division](euc.cpp)
- [`qs.cpp` - quicksort](qs.cpp)
- [`qspar.cpp` - parallel quicksort](qspar.cpp)
- [`incunabulum.c` - original J incunabulum source](incunabulum.c)
- [`incunabulum-mine.c` - heavily annotated version by me](incunabulum-mine.c)
