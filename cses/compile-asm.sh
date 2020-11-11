#!/usr/bin/env bash
filename=$(basename -s .s $1)
nasm -felf64  $1 -o build/$filename.o
ld build/$filename.o -o build/$filename.out
