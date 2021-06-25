project(ladder C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -O2 -g -Wall -fsanitize=address -fsanitize=undefined")

add_executable(a a.cpp)
add_executable(b b.cpp)
add_executable(c c.cpp)
add_executable(mcmf mcmf.cpp)

