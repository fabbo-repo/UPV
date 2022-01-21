%{
  #include <stdio.h>
  #include <string.h>
  #include "header.h"
  #include "libtds.h"
%}

/* Tipos de atributos*/
%union{ 
    char* ident; 
    int cent;
    LPC listapc;
}

/* Operadores */
%token MAS_ MENOS_ MULT_ DIV_ 
%token AND_ OR_ NOT_
%token MAYOR_ MENOR_ MAYORIG_ MENORIG_ IGUALDAD_ DESIGUALDAD_
%token IGUAL_

/* Separadores */
%token APAR_ CPAR_ ACOR_ CCOR_ ALLAV_ CLLAV_ PUNTCOMA_ COMA_ PUNTO_

/* Tipos */
%token INT_ BOOL_ 
%token STRUCT_

/* Palafras reservadas */
%token READ_ PRINT_ RETURN_
%token IF_ ELSE_ WHILE_

/* Valores booleanos */
%token TRUE_ FALSE_

/* Números y variables */
/* %token CTE_ ID_ */

/* Tokens con atributos */
%token<cent> CTE_
%token<ident> ID_

%type<cent> listaDeclaraciones declaracion declaracionVariable tipoSimple declaracionFuncion parametrosFormales
%type<cent> instruccionAsignacion
%type<cent> expresion expresionIgualdad expresionRelacional expresionAditiva expresionMultiplicativa 
%type<cent> expresionUnaria expresionSufija
%type<cent> constante parametrosActuales listaParametrosActuales
%type<cent> operadorLogico operadorIgualdad operadorRelacional operadorAditivo operadorMultiplicativo
%type<cent> operadorUnario

%type<listapc> listaParametrosFormales
%type<listapc> listaCampos


%%

programa
    :
                                            {
                                                /* Variables globales */
                                                niv = 0; /* Nivel */
                                                dvar = 0; /* Desplazamiento */
                                                cargaContexto(niv);
                                            }
    listaDeclaraciones                                              
                                            {
                                                /* En caso de 0, significa que no se ha leído una función main */
                                                if(!$2) /* Es $2 porque la acción semantica es $1 */
                                                    yyerror("El programa no tiene funcion \"main\"");
                                                else if($2>1) yyerror("El programa tiene mas de una funcion \"main\"");
                                            }
    ;

listaDeclaraciones
    : declaracion                           
                                            { $$ = $1; }
    | listaDeclaraciones declaracion                                
                                            { $$ = $1+$2; }
    ;

declaracion
    : declaracionVariable                                           
                                            { $$ = 0; /* No es una función main */}
    | declaracionFuncion                                            
                                            { $$ = $1; /* Si es una función main será 1 */}
    ;

declaracionVariable
    : tipoSimple ID_ PUNTCOMA_                                      
                                            {
                                                if(!insTdS($2, VARIABLE, $1, niv, dvar, -1)) 
                                                    yyerror("Identificador de variable repetido");
                                                else dvar += TALLA_TIPO_SIMPLE;
                                            }
    | tipoSimple ID_ ACOR_ CTE_ CCOR_ PUNTCOMA_                     
                                            { 
                                                int numelem = $4;
                                                if (numelem <= 0) {
                                                    yyerror("Talla inapropiada del array");
                                                    numelem = 0;
                                                }
                                                int ref = insTdA($1, numelem);
                                                if(!insTdS($2, VARIABLE, T_ARRAY, niv, dvar, ref))
                                                    yyerror("Identificador repetido");
                                                else dvar += numelem * TALLA_TIPO_SIMPLE; 
                                            }
    | STRUCT_ ALLAV_ 
                                            {
                                                $<cent>$=dvar;
                                                dvar = 0;
                                            }
    listaCampos CLLAV_ ID_ PUNTCOMA_               
                                            {
                                                dvar = $<cent>3;
                                                if(!insTdS($6, VARIABLE, T_RECORD, niv, dvar, $4.refe))
                                                    yyerror("Identificador repetido");
                                                else dvar += $4.tam;
                                            }
    ;

tipoSimple
    : INT_                                                          
                                            { $$ = T_ENTERO; }
    | BOOL_                                                         
                                            { $$ = T_LOGICO; }
    ;

listaCampos 
    : tipoSimple ID_ PUNTCOMA_                                      
                                            {
                                                $$.tam = TALLA_TIPO_SIMPLE;
                                                $$.refe = insTdR(-1, $2, $1, dvar);
                                                dvar += $$.tam;
                                                if($$.refe==-1)
                                                    yyerror("Nombre de campo repetido");
                                            }
    | listaCampos tipoSimple ID_ PUNTCOMA_  
                                            {
                                                $$.tam = TALLA_TIPO_SIMPLE + $1.tam;
                                                $$.refe = $1.refe;
                                                if(insTdR($1.refe, $3, $2, dvar)==-1) 
                                                    yyerror("Nombre de campo repetido");
                                                dvar += $1.tam;
                                            }
    ;

declaracionFuncion 
    : tipoSimple ID_                                                
                                            { 
                                                niv = 1; /* En C solo existen 2 niveles (0 y 1) */
                                                cargaContexto(niv);
                                            }
    APAR_ parametrosFormales CPAR_                                  
                                            {
                                                /* Si ya existe en la TdS */
                                                if(!insTdS($2, FUNCION, $1, 0, -1, $5))
                                                    yyerror("Identificador de funcion repetido");
                                                $<cent>$=dvar;
                                                dvar = 0;
                                            }
    bloque                                                          
                                            {
                                                if(verTdS) mostrarTdS();
                                                descargaContexto(niv);
                                                niv = 0;
                                                dvar = $<cent>7;
                                                if(strcmp($2, "main")==0) $$ = 1;
                                                else  $$ = 0;
                                            }
    ;
                  
parametrosFormales 
    : listaParametrosFormales                                       
                                            { $$ = $1.refe; }
    | /* vacio */                                                   
                                            { $$ = insTdD(-1, T_VACIO); }
    ;

listaParametrosFormales
    : tipoSimple ID_                                                
                                            {
                                                /* Crear una nueva entrada en la TdD */
                                                $$.refe = insTdD(-1, $1);
                                                int talla = TALLA_TIPO_SIMPLE + TALLA_SEGENLACES;
                                                $$.tam = talla;
                                                if(!insTdS($2, PARAMETRO, $1, niv, -talla, -1))
                                                    yyerror("Identificador de parametro repetido");
                                            }
    | tipoSimple ID_ COMA_ listaParametrosFormales                  
                                            {
                                                $$.refe = insTdD($4.refe, $1);
                                                int talla = TALLA_TIPO_SIMPLE + $4.tam;
                                                $$.tam = talla;
                                                if(!insTdS($2, PARAMETRO, $1, niv, -talla, -1))
                                                    yyerror("Identificador de parametro repetido");
                                            }
    ;

bloque 
    : ALLAV_ declaracionVariableLocal listaInstrucciones RETURN_ expresion PUNTCOMA_
                                            {
                                                /* Informacion de la funcion actual */
                                                INF inf = obtTdD(-1);
                                                if(inf.tipo!=T_ERROR && inf.tipo!=$5)
                                                    yyerror("Error de tipos en el \"return\"");
                                            }
    CLLAV_
    ;

declaracionVariableLocal
    : declaracionVariableLocal declaracionVariable
    | /* vacio */
    ;

listaInstrucciones
    : listaInstrucciones instruccion
    | /* vacio */
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
                                            {
                                                SIMB simb = obtTdS($1);
                                                if($3 != T_ERROR) {
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t == T_ARRAY)
                                                        yyerror("Error de asignacion a tipo \"array\"");
                                                    else if(simb.t == T_ENTERO && simb.t != $3)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"entero\"");
                                                    else if(simb.t == T_LOGICO && simb.t != $3)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"logico\"");
                                                    else if(simb.t != $3)
                                                        yyerror("Error de tipos en la \"asignacion\"");
                                                }
                                            }
    | ID_ ACOR_ expresion CCOR_ IGUAL_ expresion PUNTCOMA_          
                                            {
                                                SIMB simb = obtTdS($1);
                                                if($3 != T_ERROR && $6 != T_ERROR) {
                                                    if(simb.t == T_ERROR) 
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t != T_ARRAY)
                                                        yyerror("El identificador debe ser de tipo \"array\"");
                                                    else if ($3 != T_ENTERO)
                                                        yyerror("El indice del \"array\" debe ser entero");
                                                    else {
                                                        DIM dim = obtTdA(simb.ref);
                                                        if(dim.telem != $6)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"array\"");
                                                    } 
                                                }
                                            } 
    | ID_ PUNTO_ ID_ IGUAL_ expresion PUNTCOMA_		                
                                            {
                                                SIMB simb = obtTdS($1);
                                                if($5 != T_ERROR){
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t != T_RECORD)
                                                        yyerror("El identificador debe ser \"struct\"");
                                                    else {
                                                        CAMP campo = obtTdR(simb.ref, $3);
                                                        if(campo.t == T_ERROR)
                                                            yyerror("Campo no declarado");
                                                        else if(campo.t != $5)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"struct\"");
                                                    }
                                                }
                                            }
    ;

instruccionEntradaSalida 
    : READ_ APAR_ ID_ CPAR_ PUNTCOMA_                               
                                            {
                                                SIMB sim = obtTdS($3);
                                                if(sim.t == T_ERROR)
                                                    yyerror("Objeto no declarado");
                                                else if(sim.t!=T_ENTERO) /* read recibe un int como parametro */
                                                    yyerror("El argumento del \"read\" debe ser \"entero\"");
                                            }
    | PRINT_ APAR_ expresion CPAR_ PUNTCOMA_                        
                                            {
                                                if ($3!=T_ENTERO)
                                                    yyerror("La expresion del \"print\" debe ser \"entera\"");
                                            }
    ;

instruccionSeleccion
    : IF_ APAR_ expresion CPAR_                                     
                                            {
                                                if($3 != T_ERROR && $3 != T_LOGICO)
                                                    yyerror("La expresion del \"if\" debe ser \"logico\""); 
                                            } 
    instruccion ELSE_ instruccion
    ;

instruccionIteracion
    : WHILE_ APAR_ expresion CPAR_          
                                            {
                                                if($3 != T_ERROR && $3 != T_LOGICO)
                                                    yyerror("La expresion del \"while\" debe ser \"logica\""); 
                                            }
    instruccion
    ;

expresion
    : expresionIgualdad                                             
                                            { $$ = $1; }
    | expresion operadorLogico expresionIgualdad                    
                                            {
                                                if($1 != T_ERROR && $3 != T_ERROR) {
                                                    if($1 != $3) {
                                                        $$ = T_ERROR;
                                                        yyerror("Error de tipos en \"expresion logica\"");
                                                    }
                                                    else if($1 != T_LOGICO) {
                                                        $$ = T_ERROR;
                                                        yyerror("Operador \"logico\" debe usarse en \"expresiones logicas\"");
                                                    }
                                                    else $$ = T_LOGICO;
                                                }
                                                else $$ = T_ERROR;
                                            }
    ;

expresionIgualdad
    : expresionRelacional                                           
                                            { $$ = $1; }
    | expresionIgualdad operadorIgualdad expresionRelacional        
                                            {
                                                if($1 != T_ERROR && $3 != T_ERROR) {
                                                    if($1 != $3) {
                                                        $$ = T_ERROR;
                                                        yyerror("Error de tipos en \"expresion de igualdad\"");
                                                    }
                                                    else if($1 != T_ENTERO || $1 != T_LOGICO) {
                                                        $$ = T_ERROR;
                                                        yyerror("Operador de \"igualdad\" debe usarse con variables de tipo \"entero\" o \"logico\"");
                                                    }
                                                    else $$ = T_LOGICO;
                                                }
                                                else $$ = T_ERROR;
                                            }
    ;

expresionRelacional
    : expresionAditiva                                              
                                            { $$ = $1; }
    | expresionRelacional operadorRelacional expresionAditiva       
                                            {
                                                if($1 != T_ERROR && $3 != T_ERROR) {
                                                    if($1 != $3) {
                                                        $$ = T_ERROR;
                                                        yyerror("Error de tipos en \"expresion de relacional\"");
                                                    }
                                                    else if($1 != T_ENTERO) {
                                                        $$ = T_ERROR;
                                                        yyerror("Operador \"relacional\" debe usarse con variables de tipo \"entero\"");
                                                    }
                                                    else $$ = T_LOGICO;
                                                }
                                                else $$ = T_ERROR;
                                            }
    ;

expresionAditiva
    : expresionMultiplicativa                                       
                                            { $$ = $1; }
    | expresionAditiva operadorAditivo expresionMultiplicativa     
                                            {
                                                $$ = T_ERROR;
                                                if($1 != T_ERROR && $3 != T_ERROR) {
                                                    if($1 != $3)
                                                        yyerror("Error de tipos en \"expresion aditiva\"");
                                                    else if($1 != T_ENTERO)
                                                        yyerror("Operador \"aditivo\" debe usarse con variables de tipo \"entero\"");
                                                    else $$ = T_ENTERO;
                                                }
                                            }
    ;

expresionMultiplicativa
    : expresionUnaria                                               
                                            { $$ = $1; }
    | expresionMultiplicativa operadorMultiplicativo expresionUnaria
                                            {
                                                $$ = T_ERROR;
                                                if($1 != T_ERROR && $3 != T_ERROR) {
                                                    if($1 != $3)
                                                        yyerror("Error de tipos en \"expresion multiplicativa\"");
                                                    else if($1 != T_ENTERO)
                                                        yyerror("Operador \"multiplicativo\" debe usarse con variables de tipo \"entero\"");
                                                    else $$ = T_ENTERO;
                                                }
                                            }
    ;

expresionUnaria
    : expresionSufija                                               
                                            { $$ = $1; }
    | operadorUnario expresionUnaria                                
                                            {
                                                $$ = T_ERROR;
                                                if($2 != T_ERROR) {
                                                    if($2 == T_ENTERO) {
                                                        if($1 == NOT) 
                                                            yyerror("Operador \"!\" invalido para tipo \"entero\"");
                                                        else $$ = T_ENTERO;
                                                    }
                                                    else if($2 == T_LOGICO) {
                                                        if($1 != NOT)
                                                            yyerror("Operador \"+\" y \"-\" invalido para tipo \"logico\"");
                                                        else $$ = T_LOGICO;
                                                    }
                                                }
                                            } 
    ;

expresionSufija
    : constante                                                     
                                            { $$ = $1; }
    | APAR_ expresion CPAR_                                         
                                            { $$ = $2; }
    | ID_                                                           
                                            { 
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS($1);
                                                if(simb.t == T_ERROR) {
                                                    $$ = T_ERROR; yyerror("Objeto no declarado");
                                                }
                                                else $$ = simb.t;
                                            }
    | ID_ PUNTO_ ID_                                                
                                            {
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS($1);
                                                $$ = T_ERROR;
                                                if(simb.t == T_ERROR)
                                                    yyerror("Objeto no declarado");
                                                else if(simb.t != T_RECORD)
                                                    yyerror("El identificador debe ser \"struct\"");
                                                else {
                                                    CAMP campo = obtTdR(simb.ref, $3);
                                                    if(campo.t == T_ERROR)
                                                        yyerror("Campo no declarado");
                                                    else $$ = campo.t;
                                                }
                                            }
    | ID_ ACOR_ expresion CCOR_                                     
                                            {   
                                                SIMB simb = obtTdS($1);
                                                if(simb.t == T_ERROR) {
                                                    $$ = T_ERROR; yyerror("Objeto no declarado");
                                                }
                                                else if(simb.t != T_ARRAY ) {
                                                    $$ = T_ERROR; yyerror("El identificador debe ser de tipo \"array\"");
                                                }
                                                else {
                                                    DIM dim = obtTdA(simb.ref);
                                                    $$ = dim.telem; /* tipo de los elementos */
                                                }
                                            }
    | ID_ APAR_ parametrosActuales CPAR_                            
                                            {   
                                                SIMB simb = obtTdS($1);
                                                INF inf = obtTdD(simb.ref);
                                                if(simb.t == T_ERROR) {
                                                    $$ = T_ERROR; yyerror("Objeto no declarado");
                                                }
                                                else if(inf.tipo == T_ERROR || simb.t == T_ARRAY) { 
                                                    /* No se corresponde con ninguna función */
                                                    $$ = T_ERROR; yyerror("Indentificador no es una \"función\"");
                                                }
                                                else if(!cmpDom(simb.ref, $3)) {
                                                    /* Dominios no coinciden */
                                                    $$ = T_ERROR; yyerror("Dominios de \"funcion\" y \"parametros\" no coinciden");
                                                }
                                                else $$ = simb.t;
                                            }
    ;

constante 
    : CTE_                                                          
                                            { $$ = T_ENTERO; }
    | TRUE_                                                         
                                            { $$ = T_LOGICO; }
    | FALSE_                                                        
                                            { $$ = T_LOGICO; }
    ;

parametrosActuales
    : listaParametrosActuales                                       
                                            { $$ = $1; }
    | /* vacio */                                                   
                                            { $$ = insTdD(-1, T_VACIO); }
    ;

listaParametrosActuales
    : expresion                                                     
                                            { $$ = insTdD(-1, $1); }
    | expresion COMA_ listaParametrosActuales                       
                                            { $$ = insTdD($3, $1); }
    ;

operadorLogico
    : AND_                                                          
                                            { $$ = AND; }
    | OR_                                                           
                                            { $$ = OR; }
    ;

operadorIgualdad
    : IGUALDAD_                                                     
                                            { $$ = IGUALDAD; }
    | DESIGUALDAD_                                                  
                                            { $$ = DESIGUALDAD; }
    ;

operadorRelacional
    : MAYOR_                                
                                            { $$ = MAYOR; }
    | MENOR_
                                            { $$ = MENOR; }
    | MAYORIG_
                                            { $$ = MAYORIG; }
    | MENORIG_
                                            { $$ = MENORIG; }
    ;

operadorAditivo
    : MAS_
                                            { $$ = MAS; }
    | MENOS_
                                            { $$ = MENOS; }
    ;

operadorMultiplicativo
    : MULT_
                                            { $$ = MULT; }
    | DIV_
                                            { $$ = DIV; }
    ;

operadorUnario
    : MAS_
                                            { $$ = MAS; }
    | MENOS_
                                            { $$ = MENOS; }
    | NOT_
                                            { $$ = NOT; }
    ;

%%
