# https://codeforces.com/problemset/page/9?tags=implementation&order=BY_RATING_ASC
MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

.PHONY: a.out b.out c.out d.out f.out e.out h.out g.out

e-lca.out: e-lca.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined e-lca.cpp -o e-lca.out
	./e-lca.out

e-dsu.out: e-dsu.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined e-dsu.cpp -o e-dsu.out
	./e-dsu.out


d.out: d.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined d.cpp -o d.out -std=c++17
	# g++ -O2 d.cpp -o d.out -std=c++17
	# time ./d.out
	./d.out

b.out: b.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined b.cpp -o b.out
	./b.out


c.out: c.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined c.cpp -o c.out
	./c.out


a.out: a.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined a.cpp -o a.out
	./a.out




g.out: g.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined g.cpp -o g.out
	./g.out



h.out: h.cpp
	g++ -g -fsanitize=address -fsanitize=undefined h.cpp -std=c++17 -o h.out
	./h.out


f.out: f.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined f.cpp -o f.out
	./f.out




x.out: x.cpp
	g++ std=c++17 -g -fsanitize=address -fsanitize=undefined x.cpp -o x.out
	./x.out

