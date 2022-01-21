#include <stdio.h>

#define PI 3.1416

float areaC(float r){
    return (r*r)*PI;  
}

main() {   
   float area, radio;
   radio = 10;   
   area = areaC(radio);   
   printf("Area del circulo de radio %f es %f\n", radio, area); 
}

