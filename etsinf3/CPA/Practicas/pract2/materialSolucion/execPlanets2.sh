#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o planets2i planets2i.c -lm
gcc -fopenmp -Wall -o planets2j planets2j.c -lm

echo -e "\nResultado de ejecución de planets2i:"
OMP_NUM_THREADS=4 ./planets2i 5000

echo -e "\nResultado de ejecución de planets2j:"
OMP_NUM_THREADS=4 ./planets2j 5000
echo -e "\n"
