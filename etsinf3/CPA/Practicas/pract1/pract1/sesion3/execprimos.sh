#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o pg primo_grande_secuencial.c -lm
gcc -fopenmp -Wall -o pg1 primo_grande.c -lm

OMP_NUM_THREADS=2 ./pg
OMP_NUM_THREADS=2 ./pg1

