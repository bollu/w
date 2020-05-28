.PHONY: elementary.out treap.out

treap.out: treap.cpp
	g++ -g -O0 -std=c++17 -fsanitize=address -fsanitize=undefined treap.cpp -o treap.out
	./treap.out

elementary.out: elementary.cpp
	g++ -std=c++17 -fsanitize=address -fsanitize=undefined elementary.cpp -o elementary.out
	./elementary.out



treap-stolen.out: treap-stolen.cpp
	g++ -std=c++17 -fsanitize=address -fsanitize=undefined treap-stolen.cpp -o treap-stolen.out
	./treap-stolen.out

