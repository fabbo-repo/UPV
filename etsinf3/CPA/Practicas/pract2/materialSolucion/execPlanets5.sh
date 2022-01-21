#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o planets5 planets5.c -lm

echo -e "\nResultado de ejecución de planets5:"
OMP_NUM_THREADS=4 ./planets5 5000
