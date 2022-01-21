#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int k;  // rango del proceso (identificador)
    int p;  // numero de procesos
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &k);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    printf("Hello world! Soy proceso %d de %d procesos\n",k,p);
    
    MPI_Finalize();
    return 0;
} 