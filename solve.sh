#!/bin/bash

prob=$1
g++ input.cpp solve.cpp puzzle.cpp -o solve
./solve < "$prob"
