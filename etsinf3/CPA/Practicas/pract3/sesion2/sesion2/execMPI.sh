#!/bin/sh
#PBS -l nodes=1:ppn=8,walltime=00:10:00
#PBS -q cpa
#PBS -W x="NACCESSPOLICY:SINGLEJOB"
#PBS -d .

# Para compilar:
mpicc -Wall -o newton newton.c
mpicc -Wall -o newton_v2 newton_v2.c

#Ejecutar
mpiexec ./newton -c5
mpiexec ./newton_v2 -c5