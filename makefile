qs: qs.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -std=c++11 qs.cpp -o bin/qs
	./bin/qs
qspar: qspar.cpp
	mpic++ -g -fsanitize=address -fsanitize=undefined -std=c++11 qs.cpp -o bin/qspar
	./bin/qspar

euc: euc.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -std=c++11 euc.cpp -o bin/euc
	./bin/euc

incunabulum: incunabulum.c
	gcc -O0 -g -std=c89 -fsanitize=address -fsanitize=undefined incunabulum.c -o bin/incunabulum
	./bin/incunabulum
