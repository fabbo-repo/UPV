#include <stdio.h>

volatile int variable1 = 10;

int main(int argc, char *argv[]){
    	int variable2 = 20;
	printf("variable1 addr: %p\n", &variable1);
	printf("variable2 addr: %p\n", &variable2);
}
