#include <stdio.h> 
#define TAM_CADENA 200

void main() {
    // Puntero a caracter para copiar las cadenas
    char *p1, *p2;

    // A) Definir las variables cadena y cadena2
    char cadena[TAM_CADENA];
    char cadena2[TAM_CADENA];
     
    // B) Leer cadena de consola 
    scanf("%[^\n]s", cadena);
    // C) Convertir a mayusculas
    p1 = cadena;
    p2 = cadena2;
    while (*p1 != '\0') {
        if(*p1>='a'&&*p1<='z'){*p2=*p1-32;}
        else{*p2=*p1;}
        p1++;
        p2++;
    }
    // Acordarse de poner el cero final en cadena2
    *p2=0;
    // D) Sacar por consola la cadena2.
    printf("%s\n",cadena2);
}

