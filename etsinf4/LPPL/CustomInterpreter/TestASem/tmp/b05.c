// Ejemplo de manipulacion de funciones: 10 errores
//-------------------------------------------------

bool X[20];
bool main (int A, bool A)  // Identificador de parametro repetido
{
  bool A;                  // Identificador de variable repetido
  return 14;               // Error de tipos en el "return" 
}

int Y (int A, bool B)   
{
  int X[10];
  return X;                // En la expresion del 'return'
}

int main ()                // Identificador de funcion repetido
{
  int x; bool y;             
  x = 14;  y = true;
  if (x) {                 // La expresion del `if' debe ser 'logico'
    x = X(x, y);           // En la asignacion a una variable simple
    x = Y(y, x);           // En el dominio de los parametros actuales
  }
  else {}
  return 0;                // En la declaracion de la funcion [1]
}                          // El programa tiene mas de un `main'

// [1] El error en la declaracion de la funcion se detecta al
//     analizar la expresion del "return" ya que la declaracion
//     de la funcion no se pudo completar por un error anterior.
