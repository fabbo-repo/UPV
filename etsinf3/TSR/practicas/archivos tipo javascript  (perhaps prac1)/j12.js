
//Ejercicio de recapitulación (operaciones asíncronas y clausuras):
//     - ¿Cuál es el resultado de la ejecución de este código?
//     - Una vez contestada la cuestión anterior ejecute el código 
//       compruebe y la validez de la respuesta.

/*
for (var i=0;i<5;i++) 
   (function(){
       setTimeout( function(){console.log("---> ",i);}, i*1000 );})();

      -> Resultado son 5 líneas "---> 5" que se ejecutan respectivamente cada 1 segundo, 
      ya que el for ejecuta 5 iteraciones y cada callback accede al valor final de la i, 
      por "var i" que crea un contexto global de la i, y cada 1 segundo ya que a la vez que 
      se llama timeOut se calcula el retardo con el valor de la i de su respectiva iteración
*/
         
/*
for (var k=0;k<3;k++) 
   (function(k){
       setTimeout( 
         function(){console.log("==========> ",k);}, k*4010);})(k);

      -> Resultado son 3 líneas con resultados diferentes de 0 a 2 respectivamente cada 4.01 segundos, 
      ya que el for ejecuta 3 iteraciones y cada callback accede al valor de la k que se pasa por parametro a la function, 
      por lo que en cada contexto de las function creadas se tiene un valor diferente de k
*/
         
	   
/*
for (var x=0;x<3;x++){ 
   (function(){
	   var mm=x;
       setTimeout( function(){
		   var m=x;
		   console.log("::::::::::::::> ",m,"   ",mm);}, x*8030);})();
}
      -> Resultado son 3 líneas con resultados diferentes para mm pero mismo resultado para m, respectivamente cada 8.03 segundos, 
      ya que mm obtiene el valor de x a la vez que se llama a la function en la que se encuentra, como dicha function se invoca en cada iteración
      mm obtendrá el valor de x en su respectiva iteración (0..1..2), por otro lado m se ubica en una function que se ejecutará como un callback 
      por lo que obtendrá el valor final de x
*/


