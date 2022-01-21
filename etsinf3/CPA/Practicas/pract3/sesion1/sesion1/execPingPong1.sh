#!/bin/sh
#PBS -l nodes=1:ppn=2,walltime=00:10:00
#PBS -q cpa
#PBS -W x="NACCESSPOLICY:SINGLEJOB"
#PBS -d .

# Para compilar:
mpicc -Wall -o ping-pong ping-pong.c

# Para ver que nodos cluster han sido reservados para la ejecución:
cat $PBS_NODEFILE

#Ejecutar
mpiexec ./ping-pong 1000000