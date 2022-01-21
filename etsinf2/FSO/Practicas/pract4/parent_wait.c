/***code of parent_wait.c***/
#include <stdio.h>
#include <stdlib.h>

int main()
{ 
    int i;
    for(i=0;i<5;i++){
        int pid = fork();
        if(pid==0){
            printf("Hijo creado en iteración=%d\n",i);
            sleep(15);
            exit(i);
        }
    }
    while(wait()>0){}
    exit(0);
}