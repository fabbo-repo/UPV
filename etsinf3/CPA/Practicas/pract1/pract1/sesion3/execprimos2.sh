#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o pg3 primo_numeros.c -lm

OMP_NUM_THREADS=2 ./pg3

