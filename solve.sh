#!/bin/bash

prob=$1
if [ ! -e solve ]; then
    g++ main.cpp solve.cpp puzzle.cpp -o solve
fi
./solve < "$prob"
