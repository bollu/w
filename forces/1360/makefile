.PHONY: d.out
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
