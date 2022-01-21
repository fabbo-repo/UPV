#include <stdio.h>
#define PI 3.14
void main()
{
    int length = sizeof(char);
    char input[100];//Es un string
    int a;
    printf("El valor de PI es: %f \n",PI);
    printf("El tamaño de un char en byte es: %d\n",length);
    printf("Escribe algo con menos de 100 caracteres: ");
    gets(input);//Obtiene el input de una secuencia ordenada de caracteres
    printf("Escribiste: %s\n",input);//También se puede usar la función puts(input);
    printf("Escribe un número para escanearlo: ");
    scanf("%d",&a);//Escanea un número como input y lo guarda en la dirección de a
    //scanf lee hasta que encuentra un espacio
    printf("Escribiste: %d\n",a);

}
