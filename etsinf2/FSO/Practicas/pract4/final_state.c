/***code of final_state.c***/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX_PROC 4

int main()
{ 
    int final_state;
    pid_t val_return;
    int i;

    for(i=0;i<MAX_PROC;i++){
        val_return = fork();
        if(val_return==0){
            printf("Hijo %ld creado en iteración=%d\n",(long) getpid(),i);
            sleep(10);
        }
        else{
            printf("Padre %ld creado en iteracion=%d\n",(long) getpid(),i);
            printf("He creado un hijo %ld\n",(long) val_return);
            break;
        }
    }
    while(wait(&final_state)>0){
        printf("Padre %ld iteracion %d\n",(long)getpid(),i);
        printf("Mi hijo dijo %d\n",WEXITSTATUS(final_state));
        printf("Mi hijo dijo %d\n",final_state/256);
    }
    exit(i);
}