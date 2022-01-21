
//Clausuras de variables y funciones.

var gety;

function main(y){

	var traza="inicio"; 	// Variable que solo puede ser accedida desde la funcion main
	gety=getY; 				// Referencia al metodo getY
	return f(y);            // Referencia de f(y) con y=-100
	
	//   - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	function getY(){return y;}

	function f(y){
		var x=100+y;
		
		console.log("\ttraza: ", traza);
		
		if(x%2)return g0;   // Los valores de x pares darán false y los impares darán true
		else return g1;

		function g0(){
			traza += "-g0";
			x++;
			console.log("g0: incremento de x:  "+x);
			return f(++y);
		}
		
		function g1(){
			traza += "-g1";
			y++;
			console.log("g1: incremento de y:  "+y);
			return f(y);	
		}
	}
}


var z=main(-100);

for(var i=0; i<10;i++) z=z();

//¿Cuál es el resultado de la ejecución de la sentencia
//console.log(gety());     ->   -100
//?
