%{
  #include <stdio.h>
  #include <string.h>
  #include "header.h"
%}

/** Operadores **/
%token MAS_ MENOS_ MULT_ DIV_ 
%token OPAND_ OPOR_ OPNOT_
%token OPMAYOR_ OPMENOR_ OPMAYORIG_ OPMENORIG_ OPIGUAL_ OPDESIGUAL_
%token IGUAL_

/** Separadores **/
%token APAR_ CPAR_ ACOR_ CCOR_ ALLAV_ CLLAV_ PUNTCOMA_ COMA_ PUNTO_

/* Tipos */
%token INT_ BOOL_ 
%token STRUCT_

/** Palafras reservadas **/
%token READ_ PRINT_ RETURN_
%token IF_ ELSE_ WHILE_

/** Valores booleanos **/
%token TRUE_ FALSE_

/* Números y variables */
%token CTE_ ID_

%%

programa
    : listaDeclaraciones
    ;

listaDeclaraciones
    : declaracion
    | listaDeclaraciones declaracion
    ;

declaracion
    : declaracionVariable
    | declaracionFuncion
    ;

declaracionVariable
    : tipoSimple ID_ PUNTCOMA_
    | tipoSimple ID_ ACOR_ CTE_ CCOR_ PUNTCOMA_
    | STRUCT_ ALLAV_ listaCampos CLLAV_ ID_ PUNTCOMA_
    ;

tipoSimple
    : INT_
    | BOOL_
    ;

listaCampos 
    : tipoSimple ID_ PUNTCOMA_
    | listaCampos tipoSimple ID_ PUNTCOMA_
    ;

declaracionFuncion 
    : tipoSimple ID_ APAR_ parametrosFormales CPAR_ bloque
    ;
                  
parametrosFormales 
    : listaParametrosFormales
    | /** vacio **/
    ;

listaParametrosFormales
    : tipoSimple ID_
    | tipoSimple ID_ COMA_ listaParametrosFormales
    ;

bloque 
    : ALLAV_ declaracionVariableLocal listaInstrucciones RETURN_ expresion PUNTCOMA_ CLLAV_
    ;

declaracionVariableLocal
    : declaracionVariableLocal declaracionVariable
    | /** vacio **/
    ;

listaInstrucciones
    : listaInstrucciones instruccion
    | /** vacio **/
    ;

instruccion 
    : ALLAV_ listaInstrucciones CLLAV_ 
    | instruccionAsignacion 
    | instruccionSeleccion
    | instruccionEntradaSalida
    | instruccionIteracion
    ;

instruccionAsignacion
    : ID_ IGUAL_ expresion PUNTCOMA_ 
    | ID_ ACOR_ expresion CCOR_ IGUAL_ expresion PUNTCOMA_
    | ID_ PUNTO_ ID_ IGUAL_ expresion PUNTCOMA_
    ;

instruccionEntradaSalida 
    : READ_ APAR_ ID_ CPAR_ PUNTCOMA_
    | PRINT_ APAR_ expresion CPAR_ PUNTCOMA_
    ;

instruccionSeleccion
    : IF_ APAR_ expresion CPAR_ instruccion ELSE_ instruccion
    ;

instruccionIteracion
    : WHILE_ APAR_ expresion CPAR_ instruccion
    ;

expresion 
    : expresionIgualdad
    | expresion operadorLogico expresionIgualdad
    ;

expresionIgualdad
    : expresionRelacional
    | expresionIgualdad operadorIgualdad expresionRelacional
    ;

expresionRelacional
    : expresionAditiva
    | expresionRelacional operadorRelacional expresionAditiva
    ;

expresionAditiva
    : expresionMultiplicativa
    | expresionAditiva operadorAditivo expresionMultiplicativa
    ;

expresionMultiplicativa
    : expresionUnaria
    | expresionMultiplicativa operadorMultiplicativo expresionUnaria
    ;

expresionUnaria
    : expresionSufija
    | operadorUnario expresionUnaria
    ;

expresionSufija
    : constante 
    | APAR_ expresion CPAR_ 
    | ID_ 
    | ID_ PUNTO_ ID_ 
    | ID_ ACOR_ expresion CCOR_
    | ID_ APAR_ parametrosActuales CPAR_
    ;

constante 
    : CTE_ 
    | TRUE_ 
    | FALSE_
    ;

parametrosActuales
    : listaParametrosActuales
    | /** vacio **/
    ;

listaParametrosActuales
    : expresion 
    | expresion COMA_ listaParametrosActuales
    ;

operadorLogico
    : OPAND_ 
    | OPOR_
    ;

operadorIgualdad
    : OPIGUAL_ 
    | OPDESIGUAL_
    ;

operadorRelacional
    : OPMAYOR_
    | OPMENOR_ 
    | OPMAYORIG_
    | OPMENORIG_
    ;

operadorAditivo
    : MAS_
    | MENOS_
    ;

operadorMultiplicativo
    : MULT_
    | DIV_
    ;

operadorUnario
    : MAS_ 
    | MENOS_ 
    | OPNOT_
    ;

%%

/*****************************************************************************/
int verbosidad = TRUE;                  /* Flag si se desea una traza       */

/*****************************************************************************/
void yyerror(const char *msg)
/*  Tratamiento de errores.                                                  */
{ fprintf(stderr, "\nError en la linea %d: %s\n", yylineno, msg); }

/*****************************************************************************/
int main(int argc, char **argv) 
/* Gestiona la linea de comandos e invoca al analizador sintactico-semantico.*/
{ int i, n=1 ;

  for (i=1; i<argc; ++i)
    if (strcmp(argv[i], "-v")==0) { verbosidad = TRUE; n++; }
  if (argc == n+1)
    if ((yyin = fopen (argv[n], "r")) == NULL) {
      fprintf (stderr, "El fichero '%s' no es valido\n", argv[n]) ;     
      fprintf (stderr, "Uso: cmc [-v] fichero\n");
    } 
    else yyparse();
  else fprintf (stderr, "Uso: cmc [-v] fichero\n");

  return (0);
} 
/*****************************************************************************/
