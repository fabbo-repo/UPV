#include <stdio.h>

void primera() { printf("En primera\n"); }
void segunda() { printf("En segunda\n"); }
int main(int argc, char *argv[]) {
    printf("Soy %s\n", argv[0]);
    priera();
    segunda();
}
