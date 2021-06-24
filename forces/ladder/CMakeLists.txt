project(ladder C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -O2 -g -Wall -fsanitize=address -fsanitize=undefined")

# Constructive
# Greedy

# DP
add_executable(996a 996a.cpp)
add_executable(1472b 1472b.cpp)
add_executable(702a 702a.cpp)
add_executable(1538a 1538a.cpp)
add_executable(580a 580a.cpp)
add_executable(1501b 1501b.cpp)
add_executable(1359b 1359b.cpp)
add_executable(368b 368b.cpp)
add_executable(1345b 1345b.cpp)
add_executable(331c1 331c1.cpp)
add_executable(998b 998b.cpp)
add_executable(729b 729b.cpp)

