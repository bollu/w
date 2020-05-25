.PHONY: d.out f.out e.out h.out g.out

g.out: g.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined g.cpp -o g.out
	./g.out


h.out: h.cpp
	g++ -g -fsanitize=address -fsanitize=undefined h.cpp -std=c++17 -o h.out
	./h.out

e.out: e.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined e.cpp -o e.out
	./e.out

f.out: f.cpp
	g++ -std=c++17 -g -fsanitize=address -fsanitize=undefined f.cpp -o f.out
	./f.out

d.out: d.cpp
	g++ -g -fsanitize=address -fsanitize=undefined d.cpp -o d.out -std=c++17
	# g++ -O2 d.cpp -o d.out -std=c++17
	time ./d.out

c.out: c.cpp
	g++ -g -fsanitize=address -fsanitize=undefined c.cpp -o c.out
	./c.out

b.out: b.cpp
	g++ -g -fsanitize=address -fsanitize=undefined b.cpp -o b.out
	./b.out

a.out: a.cpp
	g++ -g -fsanitize=address -fsanitize=undefined a.cpp -o a.out
	./a.out

x.out: x.cpp
	g++ -g -fsanitize=address -fsanitize=undefined x.cpp -o x.out
	./x.out
