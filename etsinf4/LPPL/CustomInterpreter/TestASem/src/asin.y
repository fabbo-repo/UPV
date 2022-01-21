%{
  #include <stdio.h>
  #include <string.h>
  #include "header.h"
  #include "libtds.h"
  #include "libgci.h"

  int mainRef1;
  int mainRef2;
  int tallaGlobal = 0;
%}

/* Tipos de atributos*/
%union{ 
    char* ident; 
    int cent;
    LPC listapc;
    EXP exp;
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
%type<cent> parametrosActuales listaParametrosActuales
%type<cent> operadorLogico operadorIgualdad operadorRelacional operadorAditivo operadorMultiplicativo
%type<cent> operadorUnario

%type<exp> expresion expresionIgualdad expresionRelacional expresionAditiva expresionMultiplicativa 
%type<exp> expresionUnaria expresionSufija constante

%type<listapc> listaParametrosFormales
%type<listapc> listaCampos


%%

programa
    :
                                            {
                                                /* Variables globales */
                                                niv = 0; /* Nivel */
                                                dvar = 0; /* Desplazamiento */
                                                si = 0; /* Desplazamiento en el Segmento de Codigo */
                                                cargaContexto(niv);
                                                /*GCI*********************/
                                                mainRef1 = creaLans(si);
                                                emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));
                                                mainRef2 = creaLans(si);
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
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
                                                else{
                                                    dvar += TALLA_TIPO_SIMPLE;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += TALLA_TIPO_SIMPLE;
                                                }
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
                                                else{
                                                    dvar += numelem * TALLA_TIPO_SIMPLE;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += numelem * TALLA_TIPO_SIMPLE;
                                                } 
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
                                                else{
                                                    dvar += $4.tam;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += $4.tam;
                                                }
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
                                                if(strcmp($2, "main")==0) {
                                                    $$ = 1;
                                                    completaLans(mainRef1, crArgEnt(tallaGlobal));
                                                    completaLans(mainRef2, crArgEtq(si));
                                                }
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
    :                                       
                                            {
                                                emite(PUSHFP, crArgNul(), crArgNul(), crArgNul());
                                                emite(FPTOP, crArgNul(), crArgNul(), crArgNul());
                                                $<cent>$ = creaLans(si);
                                                emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));
                                            }  
    ALLAV_ declaracionVariableLocal listaInstrucciones RETURN_ expresion PUNTCOMA_
                                            {
                                                /* Informacion de la funcion actual */
                                                INF inf = obtTdD(-1);
                                                if(inf.tipo!=T_ERROR && inf.tipo!=$6.tipo)
                                                    yyerror("Error de tipos en el \"return\"");
                                                if(inf.tipo!=T_ERROR) {
                                                    int returnPos = TALLA_SEGENLACES + inf.tsp + TALLA_TIPO_SIMPLE;                                              
                                                    completaLans($<cent>1, crArgEnt(dvar)); 
                                                    emite(EASIG, crArgPos(niv, $6.valor), crArgNul(), crArgPos(niv, -returnPos));
                                                    emite(TOPFP, crArgNul(), crArgNul(), crArgNul());
                                                    emite(FPPOP, crArgNul(), crArgNul(), crArgNul());
                                                    if(strcmp(inf.nom, "main")==0)
                                                        emite(FIN, crArgNul(), crArgNul(), crArgNul());
                                                    else emite(RET, crArgNul(), crArgNul(), crArgNul());
                                                }
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
                                                if($3.tipo != T_ERROR) {
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t == T_ARRAY)
                                                        yyerror("Error de asignacion a tipo \"array\"");
                                                    else if(simb.t == T_ENTERO && simb.t != $3.tipo)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"entero\"");
                                                    else if(simb.t == T_LOGICO && simb.t != $3.tipo)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"logico\"");
                                                    else if(simb.t != $3.tipo)
                                                        yyerror("Error de tipos en la \"asignacion\"");
                                                    else{
                                                        emite(EASIG, crArgPos(niv, $3.valor), crArgNul(), crArgPos(simb.n, simb.d));
                                                    }
                                                }
                                                $$ = $3.tipo;
                                            }
    | ID_ ACOR_ expresion CCOR_ IGUAL_ expresion PUNTCOMA_          
                                            {
                                                SIMB simb = obtTdS($1);
                                                $$ = T_ERROR;
                                                if($3.tipo != T_ERROR && $6.tipo != T_ERROR) {
                                                    if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                    else if(simb.t != T_ARRAY)
                                                        yyerror("El identificador debe ser de tipo \"array\"");
                                                    else if($3.tipo != T_ENTERO)
                                                        yyerror("El indice del \"array\" debe ser entero");
                                                    else {
                                                        DIM dim = obtTdA(simb.ref);
                                                        if(dim.telem != $6.tipo)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"array\"");
                                                        else {
                                                            $$ = $6.tipo;
                                                            emite(EVA, crArgPos(simb.n, simb.d), crArgPos(niv, $3.valor), crArgPos(niv, $6.valor));
                                                        }
                                                    } 
                                                }
                                            } 
    | ID_ PUNTO_ ID_ IGUAL_ expresion PUNTCOMA_		                
                                            {
                                                SIMB simb = obtTdS($1);
                                                $$ = T_ERROR;
                                                if($5.tipo != T_ERROR){
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t != T_RECORD)
                                                        yyerror("El identificador debe ser \"struct\"");
                                                    else {
                                                        CAMP campo = obtTdR(simb.ref, $3);
                                                        if(campo.t == T_ERROR)
                                                            yyerror("Campo no declarado");
                                                        else if(campo.t != $5.tipo)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"struct\"");
                                                        else{
                                                            $$ = $6.tipo;
                                                            emite(EASIG, crArgPos(niv, $3.valor), crArgNul(), crArgPos(simb.n, simb.d+campo.d));
                                                        }
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
                                                else 
                                                    emite(EREAD, crArgNul(), crArgNul(), crArgPos(simb.n, simb.d));
                                            }
    | PRINT_ APAR_ expresion CPAR_ PUNTCOMA_                        
                                            {
                                                if ($3.tipo != T_ENTERO)
                                                    yyerror("La expresion del \"print\" debe ser \"entera\"");
                                                else
                                                    emite(EWRITE, crArgNul(), crArgNul(), crArgPos(niv, $3.valor));
                                            }
    ;

instruccionSeleccion
    : IF_ APAR_ expresion CPAR_                                     
                                            {
                                                if($3.tipo != T_ERROR && $3.tipo != T_LOGICO)
                                                    yyerror("La expresion del \"if\" debe ser \"logico\""); 
                                                $<cent>$ = creaLans(si);
                                                else emite(EIGUAL, crArgPos(niv, $3.pos), crArgEnt(0), crArgEtq(-1));
                                            } 
    instruccion 
                                            {
                                                $<cent>$ = creaLans(si);
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
                                                completaLans($<cent>5, crArgEtq(si));
                                            }
    ELSE_ instruccion                       
                                            {
                                                completaLans($<cent>7, crArgEnt(si));
                                            }
    ;

instruccionIteracion
    : WHILE_ APAR_ expresion CPAR_
                                            {
                                                if($3.tipo != T_ERROR && $3.tipo != T_LOGICO)
                                                    yyerror("La expresion del \"while\" debe ser \"logica\"");
                                                else{
                                                    /*GCI*********************/
                                                    // Si es True salta a si sino al final del WHILE
                                                    emite(EIGUAL, crArgPos(niv, $3.valor), crArgEnt(1), crArgEtq(-1));
                                                    $<instfor>$.lf = creaLans(si); 
                                                    emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
                                                    $<cent>$ = si;
                                                }
                                            }
    instruccion
                                            {
                                                /*GCI*********************/
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq($<cent>5));
                                                completaLans($<instfor>8.lf, crArgEnt(si));
                                            }
    ;

expresion
    : expresionIgualdad                                             
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor;
                                            }
    | expresion operadorLogico expresionIgualdad                    
                                            {
                                                $$.tipo = T_ERROR;
                                                if($1.tipo != T_ERROR && $3.tipo != T_ERROR) {
                                                    if($1.tipo != $3.tipo) 
                                                        yyerror("Error de tipos en \"expresion logica\"");
                                                    else if($1.tipo != T_LOGICO) 
                                                        yyerror("Operador \"logico\" debe usarse en \"expresiones logicas\"");
                                                    else {
                                                        $$.tipo = T_LOGICO;
                                                        
                                                        /*GCI*********************/
                                                        $$.d = creaVarTemp();
                                                        if($2 == EMULT) // en caso de AND
                                                            emite(EMULT, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                                        else { // en caso de OR
                                                            emite(ESUM, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                                            emite(EMENEQ, crArgPos(niv, $$.valor), crArgEnt(1), crArgEtq(si+2));
                                                            emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.valor));
                                                        }
                                                    }
                                                }
                                            }
    ;

expresionIgualdad
    : expresionRelacional                                           
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor;
                                            }
    | expresionIgualdad operadorIgualdad expresionRelacional        
                                            {
                                                $$.tipo = T_ERROR;
                                                if($1.tipo != T_ERROR && $3.tipo != T_ERROR) {
                                                    if($1.tipo != $3.tipo) 
                                                        yyerror("Error de tipos en \"expresion de igualdad\"");
                                                    else if($1.tipo != T_ENTERO || $1.tipo != T_LOGICO) 
                                                        yyerror("Operador de \"igualdad\" debe usarse con variables de tipo \"entero\" o \"logico\"");
                                                    else {
                                                        $$.tipo = T_LOGICO;
                                                        /*GCI*********************/
                                                        $$.valor = creaVarTemp();
                                                        emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.valor));
                                                        emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, si+2));
                                                        emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, $$.valor));
                                                    }
                                                }
                                            }
    ;

expresionRelacional
    : expresionAditiva                                              
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor;
                                            }
    | expresionRelacional operadorRelacional expresionAditiva       
                                            {
                                                $$.tipo = T_ERROR;
                                                if($1.tipo != T_ERROR && $3.tipo != T_ERROR) {
                                                    if($1.tipo != $3.tipo) 
                                                        yyerror("Error de tipos en \"expresion de relacional\"");
                                                    else if($1.tipo != T_ENTERO)
                                                        yyerror("Operador \"relacional\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        $$.tipo = T_LOGICO;
                                                        /*GCI*********************/
                                                        $$.valor = creaVarTemp();
                                                        emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, $$.valor));
                                                        emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, si+2));
                                                        emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, $$.valor));
                                                    }
                                                }
                                                $$.valor = creaVarTemp();
            					  emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                            }
    ;

expresionAditiva
    : expresionMultiplicativa                                       
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor;
                                            }
    | expresionAditiva operadorAditivo expresionMultiplicativa     
                                            {
                                                $$.tipo = T_ERROR;
                                                if($1.tipo != T_ERROR && $3.tipo != T_ERROR) {
                                                    if($1.tipo != $3.tipo)
                                                        yyerror("Error de tipos en \"expresion aditiva\"");
                                                    else if($1.tipo != T_ENTERO)
                                                        yyerror("Operador \"aditivo\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        $$.tipo = T_ENTERO;
                                                        /*GCI*********************/
                                                        $$.valor = creaVarTemp();
                                                        emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                                    }
                                                }
                                                $$.valor = creaVarTemp();
            					  emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                            }
    ;

expresionMultiplicativa
    : expresionUnaria                                               
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor;
                                             }
    | expresionMultiplicativa operadorMultiplicativo expresionUnaria
                                            {
                                                $$.tipo = T_ERROR;
                                                if($1.tipo != T_ERROR && $3.tipo != T_ERROR) {
                                                    if($1.tipo != $3.tipo)
                                                        yyerror("Error de tipos en \"expresion multiplicativa\"");
                                                    else if($1.tipo != T_ENTERO)
                                                        yyerror("Operador \"multiplicativo\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        $$.tipo = T_ENTERO;
                                                        /*GCI*********************/
                                                        $$.valor = creaVarTemp();
                                                        emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                                    }
                                                }
                                                $$.valor = creaVarTemp();
            					  emite($2, crArgPos(niv, $1.valor), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                            }
    ;

expresionUnaria
    : expresionSufija                                               
                                            { 
                                                $$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = $1.valor; 
                                            }
    | operadorUnario expresionUnaria                                
                                            {
                                                $$.tipo = T_ERROR;
                                                if($2.tipo != T_ERROR) {
                                                    if($2.tipo == T_ENTERO) {
                                                        if($1 == ESIG) 
                                                            yyerror("Operador \"!\" invalido para tipo \"entero\"");
                                                        else{ 
                                                            $$.tipo = T_ENTERO;
                                                            /*GCI*********************/
                                                            $$.valor = creaVarTemp();
                                                            emite(ESIG, crArgEnt(0), crArgPos(niv, $2.valor), crArgPos(niv, $$.valor));
                                                        }
                                                    }
                                                    else if($2.tipo == T_LOGICO) {
                                                        if($1 != ESIG)
                                                            yyerror("Operador \"+\" y \"-\" invalido para tipo \"logico\"");
                                                        else{
                                                            $$.tipo = T_LOGICO;
                                                            /*GCI*********************/
                                                            $$.valor = creaVarTemp();
                                                            emite(EDIF, crArgEnt(1), crArgPos(niv, $2.valor), crArgPos(niv, $$.valor));
                                                        }
                                                    }
                                                }
                                                $$.valor = creaVarTemp();
            					  if ($1 == ESIG) {
                				  	emite(EDIF, crArgEnt(1), crArgPos(niv, $2.valor), crArgPos(niv, $$.valor));    
            					  } else {
                				  	emite($1, crArgEnt(0), crArgPos(niv, $2.valor), crArgPos(niv, $$.valor));
            					  }
                                            } 
    ;

expresionSufija
    : constante                                                     
                                            { 
                                            	$$.tipo = $1.tipo;
                                                /*GCI*********************/
                                                $$.valor = creaVarTemp();
                                                emite(EASIG, crArgEnt($1.valor), crArgNul(), crArgPos(niv, $$.valor)); 
                                            }
    | APAR_ expresion CPAR_                                         
                                            { 
                                                $$.tipo = $2.tipo;
                                                /*GCI*********************/
                                                $$.valor = $2.valor;
                                            }
    | ID_                                                           
                                            { 
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS($1);
                                                if(simb.t == T_ERROR) {
                                                    $$.tipo = T_ERROR; yyerror("Objeto no declarado");
                                                }
                                                else{
                                                    $$.tipo = simb.t;
                                                    /*GCI*********************/
                                                    $$.valor = creaVarTemp();
                                                    emite(EASIG, crArgPos(simb.n, simb.d), crArgNul(), crArgPos(niv, $$.valor));
                                                }
                                            }
    | ID_ PUNTO_ ID_                                                
                                            {
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS($1);
                                                $$.tipo = T_ERROR;
                                                if(simb.t == T_ERROR)
                                                    yyerror("Objeto no declarado");
                                                else if(simb.t != T_RECORD)
                                                    yyerror("El identificador debe ser \"struct\"");
                                                else {
                                                    CAMP campo = obtTdR(simb.ref, $3);
                                                    if(campo.t == T_ERROR)
                                                        yyerror("Campo no declarado");
                                                    else $$.tipo = campo.t;
                                                    /*GCI*********************/
                                                    int pos = simb.d + campo.d;
                                                    $$.valor = creaVarTemp();
                                                    emite(EASIG, crArgPos(simb.n, pos), crArgNul(), crArgPos(niv, $$.valor));
                                                }
                                            }
    | ID_ ACOR_ expresion CCOR_                                     
                                            {   
                                                SIMB simb = obtTdS($1);
                                                $$.tipo = T_ERROR;
                                                if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                else if(simb.t != T_ARRAY ) yyerror("El identificador debe ser de tipo \"array\"");
                                                else {
                                                    DIM dim = obtTdA(simb.ref);
                                                    $$.tipo = dim.telem; /* tipo de los elementos */
                                                    /*GCI*********************/
                                                    $$.valor = creaVarTemp();
                                                    emite(EAV, crArgPos(simb.n, simb.d), crArgPos(niv, $3.valor), crArgPos(niv, $$.valor));
                                                }
                                            }
    | ID_ APAR_ parametrosActuales CPAR_                            
					                        {   
                                                SIMB simb = obtTdS($1);
                                                INF inf = obtTdD(simb.ref);
                                                $$.tipo = T_ERROR;
                                                if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                else if(inf.tipo == T_ERROR || simb.t == T_ARRAY) 
                                                    yyerror("Indentificador no es una \"función\"");
                                                else if(!cmpDom(simb.ref, $3)) {
                                                    /* Dominios no coinciden */
                                                    yyerror("Dominios de \"funcion\" y \"parametros\" no coinciden");
                                                }
                                                else {
                                                    $$.tipo = inf.tipo;
                                                    /*GCI*********************/
                                                    emite(CALL, crArgNul(), crArgNul(), crArgEtq(simb.d));
                                                    emite(DECTOP, crArgNul(), crArgNul(), crArgEnt(inf.tsp));
                                                    $$.valor = creaVarTemp();
                                                    emite(EPOP, crArgNul(), crArgNul(), crArgPos(niv, $$.valor));
                                                }
					                        }
    ;

constante 
    : CTE_                                                          
                                            {
                                                $$.tipo = T_ENTERO;
                                                /*GCI*********************/
                                                $$.valor = $1; // Valor
                                            }
    | TRUE_                                                         
                                            {
                                                $$.tipo = T_LOGICO;
                                                /*GCI*********************/
                                                $$.valor = 1; // Valor
                                            }
    | FALSE_                                                        
                                            {
                                                $$.tipo = T_LOGICO;
                                                /*GCI*********************/
                                                $$.valor = 0; // Valor
                                            }
    ;
    ;

parametrosActuales
    : listaParametrosActuales                                       
                                            { $$ = $1; }
    | /* vacio */                                                   
                                            { $$ = insTdD(-1, T_VACIO); }
    ;

listaParametrosActuales
    : expresion                                                     
                                            { 
                                            	$$ = insTdD(-1, $1.tipo); 
                                                /*GCI*********************/
                                            	emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, $1.valor));
                                            }
    | expresion 			     
                                            {
                                                /*GCI*********************/
                                                emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, $1.valor));
                                            }
      COMA_ listaParametrosActuales                       
                                            { $$ = insTdD($4, $1.tipo); }
    ;

operadorLogico
    : AND_                                                          
                                            { $$ = EMULT; }
    | OR_                                                           
                                            { $$ = ESUM; }
    ;

operadorIgualdad
    : IGUALDAD_                                                     
                                            { $$ = EIGUAL; }
    | DESIGUALDAD_                                                  
                                            { $$ = EDIST; }
    ;

operadorRelacional
    : MAYOR_                                
                                            { $$ = EMAY; }
    | MENOR_
                                            { $$ = EMEN; }
    | MAYORIG_
                                            { $$ = EMAYEQ; }
    | MENORIG_
                                            { $$ = EMENEQ; }
    ;

operadorAditivo
    : MAS_
                                            { $$ = ESUM; }
    | MENOS_
                                            { $$ = EDIF; }
    ;

operadorMultiplicativo
    : MULT_
                                            { $$ = EMULT; }
    | DIV_
                                            { $$ = EDIVI; }
    ;

operadorUnario
    : MAS_
                                            { $$ = ESUM; }
    | MENOS_
                                            { $$ = EDIF; }
    | NOT_
                                            { $$ = ESIG; }
    ;

%%
