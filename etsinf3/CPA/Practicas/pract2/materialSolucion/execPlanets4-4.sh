#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o planets2i planets2i.c -lm
gcc -fopenmp -Wall -o planets2j planets2j.c -lm

echo -e "\nResultado de ejecución de planets2i:  (4 hilos)"
OMP_NUM_THREADS=4 OMP_SCHEDULE=static,0 ./planets2i 60000
echo -e "----------------------------------------------------"
echo -e "Resultado de ejecución de planets2j:  (4 hilos)"
OMP_NUM_THREADS=4 OMP_SCHEDULE=static,0 ./planets2j 60000
