#!/bin/sh
#PBS -l nodes=2:ppn=8,walltime=00:10:00
#PBS -q cpa
#PBS -W x="NACCESSPOLICY:SINGLEJOB"
#PBS -d .

# Para compilar:
mpicc -Wall -o sistbfMod sistbfMod.c
mpicc -Wall -o sistbf sistbf.c

#Ejecutar
mpiexec ./sistbf 1000
mpiexec ./sistbfMod 1000