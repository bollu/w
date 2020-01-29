xor-and-insert: xor-and-insert.cpp
	g++ -O0 -g -std=c++17 -fsanitize=address -fsanitize=undefined xor-and-insert.cpp -o bin/xor-and-insert

help-ashu: help-ashu.cpp
	g++ -O0 -g -std=c++17 -fsanitize=address -fsanitize=undefined help-ashu.cpp -o bin/help-ashu

generalized-flow: generalized-flow.cpp
	g++ -g -O0 -std=c++17 -fsanitize=address -fsanitize=undefined generalized-flow.cpp -o bin/generalized-flow

segtree-lazy-generic: segtree-lazy-generic.cpp
	g++ -O0 -g -std=c++17 -fsanitize=address -fsanitize=undefined segtree-lazy-generic.cpp -o bin/segtree-lazy-generic

doomsday: doomsday.cpp
	g++ -g -std=c++17 -fsanitize=address -fsanitize=undefined doomsday.cpp -o bin/doomsday

qs: qs.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -std=c++11 qs.cpp -o bin/qs
	./bin/qs
qspar: qspar.cpp
	mpic++ -g -fsanitize=address -fsanitize=undefined -std=c++11 qs.cpp -o bin/qspar
	./bin/qspar

euc: euc.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -std=c++11 euc.cpp -o bin/euc
	./bin/euc

segtree: segtree.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -std=c++11 segtree.cpp -o bin/segtree
	./bin/segtree

segtree-recur-point: segtree-recur-point.cpp
	g++ -O0 -g -std=c++11 -fsanitize=address -fsanitize=undefined segtree-recur-point.cpp -o bin/segtree-recur-point
	./bin/segtree-recur-point

incunabulum: incunabulum.c
	gcc -O0 -g -std=c89 -fsanitize=address -fsanitize=undefined incunabulum.c -o bin/incunabulum
	./bin/incunabulum

incunabulum-mine: incunabulum-mine.c
	gcc -O0 -g -std=c89 -fsanitize=address -fsanitize=undefined incunabulum-mine.c -o bin/incunabulum-mine
	./bin/incunabulum-mine

XXXX: XXXX.cpp
	g++ -O0 -g -std=c++17 -fsanitize=address -fsanitize=undefined XXXX.cpp -o bin/XXXX
