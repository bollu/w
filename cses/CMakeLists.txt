cmake_minimum_required(VERSION 3.4.3)
project(cscs C CXX)

# Colors when compiling with clang
# set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fno-rtti -g -Wall -Werror")
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fno-rtti -g -Wall -fsanitize=address -fsanitize=undefined -static-libasan")

add_executable(distinct-numbers.out distinct-numbers.cpp)
set_target_properties(distinct-numbers.out PROPERTIES CXX_STANDARD 17)

add_executable(apartments.out apartments.cpp)
set_target_properties(apartments.out PROPERTIES CXX_STANDARD 17)

add_executable(ferris-wheel.out ferris-wheel.cpp)
set_target_properties(ferris-wheel.out PROPERTIES CXX_STANDARD 17)

add_executable(concert-tickets.out concert-tickets.cpp)
set_target_properties(concert-tickets.out PROPERTIES CXX_STANDARD 17)

add_executable(restaurant-customers.out restaurant-customers.cpp)
set_target_properties(restaurant-customers.out PROPERTIES CXX_STANDARD 17)

add_executable(movie-festival.out movie-festival.cpp)
set_target_properties(movie-festival.out PROPERTIES CXX_STANDARD 17)

add_executable(sum-of-two-values.out sum-of-two-values.cpp)
set_target_properties(sum-of-two-values.out PROPERTIES CXX_STANDARD 17)

add_executable(maximum-subarray-sum.out maximum-subarray-sum.cpp)
set_target_properties(maximum-subarray-sum.out PROPERTIES CXX_STANDARD 17)

add_executable(stick-lengths.out stick-lengths.cpp)
set_target_properties(stick-lengths.out PROPERTIES CXX_STANDARD 17)

add_executable(playlist.out playlist.cpp)
set_target_properties(playlist.out PROPERTIES Cplaylist_STANDARD 17)

add_executable(XX.out XX.cpp)
set_target_properties(XX.out PROPERTIES CXX_STANDARD 17)
