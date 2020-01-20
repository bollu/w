.PHONY: a.out b.out c.out d.out

a.out: 
	g++ -g -std=c++11 -O2 -Wall -Werror -fsanitize=address -fsanitize=undefined a.cpp -o a.out
	./a.out < a.in

b.out: 
	g++ -g -std=c++11 -O2 -Wall -Werror -fsanitize=address -fsanitize=undefined b.cpp -o b.out
	./b.out < b.in

c.out: 
	g++ -g -std=c++11 -O2 -Wall -Werror -fsanitize=address -fsanitize=undefined c.cpp -o c.out
	./c.out < c.in

d.out: 
	g++ -g -std=c++17 -O2 -Wall -Werror -fsanitize=address -fsanitize=undefined d.cpp -o d.out
	./d.out < d.in1
	./d.out < d.in2
	./d.out < d.in3

# take screenshot of https://codeforces.com/contest/1293/problems
