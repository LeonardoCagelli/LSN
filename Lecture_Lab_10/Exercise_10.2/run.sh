#!/bin/bash

# Perform make clean
make clean

# Compile main.exe
make

# Run main.exe
time mpiexec -n 4 ./Exercise_10.2.exe
