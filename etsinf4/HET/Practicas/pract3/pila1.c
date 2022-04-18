#include <stdio.h>

void cuarta(int o){
}

void tercera(int z){ 
	cuarta(z+1);
}

void segunda(int y){ 
	tercera(y+1);
}

void primera(int x){ 
	segunda(x);
}

int main(int argc, char *argv[]){
	primera(5);
}
