#include <stdio.h>

void main(int argc, char *argv[]) {   
     int i;
     printf("Número argumentos: %d",argc);
     for(i=0;i<argc;i++){printf("\nArgumento %d: %s",i,argv[i]);}
}

