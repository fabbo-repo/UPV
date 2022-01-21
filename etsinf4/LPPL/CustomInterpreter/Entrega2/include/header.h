/*****************************************************************************/
/*****************************************************************************/
#ifndef _HEADER_H
#define _HEADER_H

/****************************************************** Constantes generales */
#define TRUE  1
#define FALSE 0
#define TALLA_TIPO_SIMPLE 1            /* Talla asociada a los tipos simples */
#define TALLA_SEGENLACES 2       /* Talla del segmento de Enlaces de Control */

/************************************************** Constantes de operadores */
#define AND 0
#define OR 1
#define IGUALDAD 2
#define DESIGUALDAD 3
#define MAYOR 4
#define MENOR 5
#define MAYORIG 6
#define MENORIG 7
#define MAS 8
#define MENOS 9
#define MULT 10
#define DIV 11
#define NOT 12

/***************************************************** Estructuras generales */
typedef struct listapc   /** Estructura para la lista de parametros y campos */
{              
  int tam;
  int refe;
} LPC;

/************************************* Variables externas definidas en el AL */
extern int yylex();
extern int yyparse();

extern FILE *yyin;
extern int   yylineno;
/********************************* Funciones y variables externas auxiliares */
extern int verbosidad;                   /* Flag si se desea una traza       */

/************************ Variables externas definidas en Programa Principal */
extern int verTdS; /* Flag para saber si mostrar la TdS */

/***************************** Variables externas definidas en las librerías */
extern int dvar;               /* Desplazamiento en el Segmento de Variables */
extern int niv;                   /* Nivel de anidamiento "global" o "local" */

extern void yyerror(const char * msg) ;   /* Tratamiento de errores          */

#endif  /* _HEADER_H */
/*****************************************************************************/
/*****************************************************************************/
