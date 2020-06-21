segsieve: segsieve.cpp
	g++ -std=c++17 -O3 segsieve.cpp -o segsieve.out
	time ./segsieve.out

primeslin: primeslin.cpp
	g++ -std=c++17 -O3 primeslin.cpp -o primeslin.out -mcmodel=medium 
	time ./primeslin.out

primes: primes.cpp
	# g++ -g -std=c++17 -fsanitize=address -fsanitize=undefined primes.cpp -o primes.out -mcmodel=medium
	g++ -std=c++17 -O3 primes.cpp -o primes.out -mcmodel=medium 
	time ./primes.out > primes-out-file
	
primes2c: primes2c.c
	# g++ -std=c++17 -fsanitize=address -fsanitize=undefined primes2.cpp -o primes2.out
	gcc -std=c++17 -O3 primes2c.c -o primes2c.out
	time ./primes2c.out

millerrabin: millerrabin.cpp
	g++ -std=c++17 -O3 millerrabin.cpp -o millerrabin.out
	time ./millerrabin.out


primes2: primes2.cpp
	# g++ -std=c++17 -fsanitize=address -fsanitize=undefined primes2.cpp -o primes2.out
	g++ -std=c++17 -O3 primes2.cpp -o primes2.out
	time ./primes2.out


brckts: brckts.cpp
	g++ -std=c++17 -fsanitize=address -fsanitize=undefined brckts.cpp -o brckts.out
