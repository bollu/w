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

add_executable(increasing-subsequence.out increasing-subsequence.cpp)
set_target_properties(increasing-subsequence.out PROPERTIES CXX_STANDARD 17)

add_executable(range-sum-queries-1.out range-sum-queries-1.cpp)
set_target_properties(range-sum-queries-1.out PROPERTIES CXX_STANDARD 17)

add_executable(range-sum-queries-II.out range-sum-queries-II.cpp)
set_target_properties(range-sum-queries-II.out PROPERTIES CXX_STANDARD 17)

add_executable(range-minimum-queries-II.out range-minimum-queries-II.cpp)
set_target_properties(range-minimum-queries-II.out PROPERTIES CXX_STANDARD 17)

add_executable(range-xor-queries.out range-xor-queries.cpp)
set_target_properties(range-xor-queries.out PROPERTIES CXX_STANDARD 17)

add_executable(range-update-queries.out range-update-queries.cpp)
set_target_properties(range-update-queries.out PROPERTIES CXX_STANDARD 17)

add_executable(forest-queries.out forest-queries.cpp)
set_target_properties(forest-queries.out PROPERTIES CXX_STANDARD 17)

add_executable(hotel-queries.out hotel-queries.cpp)
set_target_properties(hotel-queries.out PROPERTIES CXX_STANDARD 17)

add_executable(list-removals.out list-removals.cpp)
set_target_properties(list-removals.out PROPERTIES CXX_STANDARD 17)

add_executable(salary-queries.out salary-queries.cpp)
set_target_properties(salary-queries.out PROPERTIES CXX_STANDARD 17)

add_executable(forest-queries-II.out forest-queries-II.cpp)
set_target_properties(forest-queries-II.out PROPERTIES CXX_STANDARD 17)

add_executable(counting-rooms.out counting-rooms.cpp)
set_target_properties(counting-rooms.out PROPERTIES CXX_STANDARD 17)

add_executable(labyrinth.out labyrinth.cpp)
set_target_properties(labyrinth.out PROPERTIES CXX_STANDARD 17)

add_executable(building-roads.out building-roads.cpp)
set_target_properties(building-roads.out PROPERTIES CXX_STANDARD 17)

add_executable(message-route.out message-route.cpp)
set_target_properties(message-route.out PROPERTIES CXX_STANDARD 17)

add_executable(building-teams.out building-teams.cpp)
set_target_properties(building-teams.out PROPERTIES CXX_STANDARD 17)

add_executable(round-trip.out round-trip.cpp)
set_target_properties(round-trip.out PROPERTIES CXX_STANDARD 17)

add_executable(monsters.out monsters.cpp)
set_target_properties(monsters.out PROPERTIES CXX_STANDARD 17)

add_executable(shortest-routes-I.out shortest-routes-I.cpp)
set_target_properties(shortest-routes-I.out PROPERTIES CXX_STANDARD 17)

add_executable(shortest-routes-II.out shortest-routes-II.cpp)
set_target_properties(shortest-routes-II.out PROPERTIES CXX_STANDARD 17)

add_executable(high-score.out high-score.cpp)
set_target_properties(high-score.out PROPERTIES CXX_STANDARD 17)

add_executable(flight-discount.out flight-discount.cpp)
set_target_properties(flight-discount.out PROPERTIES CXX_STANDARD 17)

add_executable(cycle-finding.out cycle-finding.cpp)
set_target_properties(cycle-finding.out PROPERTIES CXX_STANDARD 17)

add_executable(flight-routes.out flight-routes.cpp)
set_target_properties(flight-routes.out PROPERTIES CXX_STANDARD 17)

add_executable(round-trip-II.out round-trip-II.cpp)
set_target_properties(round-trip-II.out PROPERTIES CXX_STANDARD 17)

add_executable(course-schedule.out course-schedule.cpp)
set_target_properties(course-schedule.out PROPERTIES CXX_STANDARD 17)

add_executable(longest-flight-route.out longest-flight-route.cpp)
set_target_properties(longest-flight-route.out PROPERTIES CXX_STANDARD 17)

add_executable(game-routes.out game-routes.cpp)
set_target_properties(game-routes.out PROPERTIES CXX_STANDARD 17)

add_executable(investigation.out investigation.cpp)
set_target_properties(investigation.out PROPERTIES CXX_STANDARD 17)

add_executable(planet-queries-I.out planet-queries-I.cpp)
set_target_properties(planet-queries-I.out PROPERTIES CXX_STANDARD 17)

add_executable(planet-queries-II.out planet-queries-II.cpp)
set_target_properties(planet-queries-II.out PROPERTIES CXX_STANDARD 17)

add_executable(subordinates.out subordinates.cpp)
set_target_properties(subordinates.out PROPERTIES CXX_STANDARD 17)

add_executable(tree-matching.out tree-matching.cpp)
set_target_properties(tree-matching.out PROPERTIES CXX_STANDARD 17)

add_executable(tree-diameter.out tree-diameter.cpp)
set_target_properties(tree-diameter.out PROPERTIES CXX_STANDARD 17)


add_executable(company-queries-I.out company-queries-I.cpp)
set_target_properties(company-queries-I.out PROPERTIES CXX_STANDARD 17)

add_executable(company-queries-II.out company-queries-II.cpp)
set_target_properties(company-queries-II.out PROPERTIES CXX_STANDARD 17)

add_executable(distance-queries.out distance-queries.cpp)
set_target_properties(distance-queries.out PROPERTIES CXX_STANDARD 17)


add_executable(YY.out YY.cpp)
set_target_properties(YY.out PROPERTIES CXX_STANDARD 17)
