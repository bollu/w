cmake_minimum_required(VERSION 3.4.3)
project(cscs C CXX)

# Colors when compiling with clang
# set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fno-rtti -g -Wall -Werror")
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fno-rtti -g -Wall -fsanitize=address -fsanitize=undefined")

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
set_target_properties(playlist.out PROPERTIES CXX_STANDARD 17)

add_executable(towers.out towers.cpp)
set_target_properties(towers.out PROPERTIES CXX_STANDARD 17)

add_executable(nearest-smaller-values.out nearest-smaller-values.cpp)
set_target_properties(nearest-smaller-values.out PROPERTIES CXX_STANDARD 17)

add_executable(traffic-lights.out traffic-lights.cpp)
set_target_properties(traffic-lights.out PROPERTIES CXX_STANDARD 17)

add_executable(room-allocation.out room-allocation.cpp)
set_target_properties(room-allocation.out PROPERTIES CXX_STANDARD 17)

add_executable(factory-machines.out factory-machines.cpp)
set_target_properties(factory-machines.out PROPERTIES CXX_STANDARD 17)

add_executable(tasks-and-deadlines.out tasks-and-deadlines.cpp)
set_target_properties(tasks-and-deadlines.out PROPERTIES CXX_STANDARD 17)

add_executable(reading-books.out reading-books.cpp)
set_target_properties(reading-books.out PROPERTIES CXX_STANDARD 17)

add_executable(sum-of-three-values.out sum-of-three-values.cpp)
set_target_properties(sum-of-three-values.out PROPERTIES CXX_STANDARD 17)

add_executable(sum-of-four-values.out sum-of-four-values.cpp)
set_target_properties(sum-of-four-values.out PROPERTIES CXX_STANDARD 17)

add_executable(subarray-sums-1.out subarray-sums-1.cpp)
set_target_properties(subarray-sums-1.out PROPERTIES CXX_STANDARD 17)

add_executable(subarray-sums-2.out subarray-sums-2.cpp)
set_target_properties(subarray-sums-2.out PROPERTIES CXX_STANDARD 17)

add_executable(subarray-divisibility.out subarray-divisibility.cpp)
set_target_properties(subarray-divisibility.out PROPERTIES CXX_STANDARD 17)

add_executable(sliding-median.out sliding-median.cpp)
set_target_properties(sliding-median.out PROPERTIES CXX_STANDARD 17)


add_executable(dice-combinations.out dice-combinations.cpp)
set_target_properties(dice-combinations.out PROPERTIES CXX_STANDARD 17)

add_executable(minimizing-coins.out minimizing-coins.cpp)
set_target_properties(minimizing-coins.out PROPERTIES CXX_STANDARD 17)

add_executable(coin-combinations-1.out coin-combinations-1.cpp)
set_target_properties(coin-combinations-1.out PROPERTIES CXX_STANDARD 17)

add_executable(coin-combinations-2.out coin-combinations-2.cpp)
set_target_properties(coin-combinations-2.out PROPERTIES CXX_STANDARD 17)

add_executable(removing-digits.out removing-digits.cpp)
set_target_properties(removing-digits.out PROPERTIES CXX_STANDARD 17)

add_executable(grid-paths.out grid-paths.cpp)
set_target_properties(grid-paths.out PROPERTIES CXX_STANDARD 17)

add_executable(book-shop.out book-shop.cpp)
set_target_properties(book-shop.out PROPERTIES CXX_STANDARD 17)

add_executable(edit-distance.out edit-distance.cpp)
set_target_properties(edit-distance.out PROPERTIES CXX_STANDARD 17)

add_executable(array-description.out array-description.cpp)
set_target_properties(array-description.out PROPERTIES CXX_STANDARD 17)

add_executable(money-sums.out money-sums.cpp)
set_target_properties(money-sums.out PROPERTIES CXX_STANDARD 17)

add_executable(rectangle-cutting.out rectangle-cutting.cpp)
set_target_properties(rectangle-cutting.out PROPERTIES CXX_STANDARD 17)

add_executable(removal-game.out removal-game.cpp)
set_target_properties(removal-game.out PROPERTIES CXX_STANDARD 17)

add_executable(two-sets-II.out two-sets-II.cpp)
set_target_properties(two-sets-II.out PROPERTIES CXX_STANDARD 17)

add_executable(YY.out YY.cpp)
set_target_properties(YY.out PROPERTIES CXX_STANDARD 17)
