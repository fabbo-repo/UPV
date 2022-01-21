#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

gcc -fopenmp -Wall -o image1 imagenes1.c -lm
gcc -fopenmp -Wall -o imageV1 imageV1.c -lm
gcc -fopenmp -Wall -o imageV2 imageV2.c -lm
gcc -fopenmp -Wall -o imageV3 imageV3.c -lm
gcc -fopenmp -Wall -o imageV4 imageV4.c -lm

OMP_NUM_THREADS=2 ./image1
OMP_NUM_THREADS=4 ./imageV1
OMP_NUM_THREADS=4 ./imageV2
OMP_NUM_THREADS=4 ./imageV3
OMP_NUM_THREADS=4 ./imageV4

OMP_NUM_THREADS=8 ./imageV1
OMP_NUM_THREADS=8 ./imageV2
OMP_NUM_THREADS=8 ./imageV3
OMP_NUM_THREADS=8 ./imageV4

