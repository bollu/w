#!/usr/bin/env bash
set -e
clang++ -std=c++17 -Wall -Werror -fsanitize=address -fsanitize=undefined $1 -o $(basename $1 .cpp).out
echo "---"
./$(basename $1 .cpp).out
