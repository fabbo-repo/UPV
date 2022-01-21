/***code of range_process.c***/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    int i;
    for(i=0;i<5;i++){
        int pid = fork();
        if(pid==0){
            printf("Hijo creado en iteración=%d\n",i);
            exit(i);
        }
    }
    sleep(10);
    exit(0);
}