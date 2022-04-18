#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char global[100];

void vulnerable(){
    char local[32];
    gets(local);
    strcpy(global, local);
}

int main(void){
    printf("Yo soy:\n");
    system("/usr/bin/id");
    vulnerable();
    return 0;
}
