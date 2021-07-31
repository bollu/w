project(contest C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -O2 -g -Wall -fsanitize=address -fsanitize=undefined")

add_executable(g g.cpp)
add_executable(h h.cpp)
add_executable(i i.cpp)
add_executable(l l.cpp)	

