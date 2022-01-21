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
  return 2;
}

int main2() 
{
  bool x; bool y;             
  x = 14;  y = true;       // Error de tipos en la "asignacion"
  if (x) {
    x = Y(2, y);           // Error de tipos en la "asignacion"
  }
  else {}
  return 0;                
}                          