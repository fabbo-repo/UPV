%{
  #include <stdio.h>
  #include <string.h>
  #include "header.h"

  #define  retornar(x) { if (verbosidad) ECHO; }
%}
/*-----------------------------------------------------------------------------
  Estas opciones evitan "warnings" innecesarios y permiten obtener el
  numero de linea actual en la variable global "yylineno".
-----------------------------------------------------------------------------*/
%option noinput       
%option nounput
%option yylineno  

delimitador       [ \t\n]+
comentario      	\/\/.*
digito            [0-9]
letra             [a-zA-Z]
entero            {digito}*
real              {digito}*\.{digito}+|{digito}+\.
constante         ({entero}|{real})
identificador     {letra}({letra}|{digito}|_)*

%%

{comentario}    { if (verbosidad) ECHO; }
{delimitador}   { if (verbosidad) ECHO; }

"+"	            { retornar(MAS_);   }
"-"             { retornar(MENOS_); }
"*"             { retornar(MULT_);   }
"/"             { retornar(DIV_);   }
"&&"				    { retornar(OPAND_); }
"||"				    { retornar(OPOR_); }
"!"					    { retornar(OPNOT_); }
">"					    { retornar(OPMAYOR_); }
"<"					    { retornar(OPMENOR_); }
">="			 	    { retornar(OPMAYORIG_); }
"<="				    { retornar(OPMENORIG_); }
"=="			 	    { retornar(OPIGUAL_); }
"!="				    { retornar(OPDESIGUAL_); }
"="				 	    { retornar(IGUAL_); }

"("             { retornar(APAR_);  }
")"             { retornar(CPAR_);  }
"["             { retornar(ACOR_);  }
"]"             { retornar(CCOR_);  }
"{"             { retornar(ALLAV_);  }
"}"             { retornar(CLLAV_);  }

"while"				  { retornar(WHILE_); }
"if"				    { retornar(IF_); }
"else"				  { retornar(ELSE_); }
"int"				    { retornar(INT_); }
"bool"			    { retornar(BOOL_); }
"read"				  { retornar(READ_); }
"print"				  { retornar(PRINT_); }
"return"			  { retornar(RETURN_); }
"struct"			  { retornar(STRUCT_); }

"true"				  { retornar(TRUE_); }
"false"				  { retornar(FALSE_); }

";"             { retornar(PUNTCOMA_); }
","             { retornar(COMA_); }
"."             { retornar(PUNTO_); }

{constante}     { retornar(CTE_) }
{identificador} { retornar(ID_) }

.	              { yyerror("Caracter desconocido"); }
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
    else yylex ();
  else fprintf (stderr, "Uso: cmc [-v] fichero\n");

  return (0);
} 
/*****************************************************************************/
