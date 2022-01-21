%{
  #include <stdio.h>
  #include <string.h>
  #include "header.h"
  #include "asin.h"

  #define  retornar(x) { if (verbosidad) ECHO; return(x); }
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
"&&"				    { retornar(AND_); }
"||"				    { retornar(OR_); }
"!"					    { retornar(NOT_); }
">"					    { retornar(MAYOR_); }
"<"					    { retornar(MENOR_); }
">="			 	    { retornar(MAYORIG_); }
"<="				    { retornar(MENORIG_); }
"=="			 	    { retornar(IGUALDAD_); }
"!="				    { retornar(DESIGUALDAD_); }
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

 /* atoi: covierte string a int, si lee un real directamente lo castea a int */
{constante}     { yylval.cent = atoi(yytext); retornar(CTE_); }
 /* strdup: devuelve un string duplicado (una copia) */
{identificador} { yylval.ident = strdup(yytext); retornar(ID_) }

.	              { printf("Error en [%d]: %s\n", yylineno, yytext); yyerror("Caracter desconocido"); }
%%
