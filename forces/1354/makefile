.PHONY: a b c1 d

d:
	gcc -g -fsanitize=address -fsanitize=undefined  d.cpp -o d -ffast-math -lstdc++
	./d
c2: c2.cpp
	gcc -g -fsanitize=address -fsanitize=undefined  c2.cpp -o c2 -std=c++17 -lstdc++ -lm
	./c2

c1: c1.cpp
	gcc -g -fsanitize=address -fsanitize=undefined  c1.cpp -o c1 -std=c++17 -lstdc++ -lm
	./c1

b: b.cpp
	gcc -g -fsanitize=address -fsanitize=undefined  b.cpp -o b -std=c++17 -lstdc++
	./b

a: a.cpp
	gcc -g -fsanitize=address -fsanitize=undefined  a.cpp -o a -std=c++17 -lstdc++
	./a
