#!/bin/sh
#PBS -l nodes=2:ppn=16,walltime=00:10:00
#PBS -q cpa
#PBS -W x="NACCESSPOLICY:SINGLEJOB"
#PBS -d .

# Para compilar:
mpicc -Wall -o hello hello.c

# Para ver que nodos cluster han sido reservados para la ejecución:
cat $PBS_NODEFILE

#Ejecutar
mpiexec ./hello