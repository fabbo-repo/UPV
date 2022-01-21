// Ejemplo de manipulacion de registros. Lee un numero ("x")
// y devuelve "0" si "x > 0" y "1" en caso contrario.
//----------------------------------------------------------
struct { int a; bool b; int c; } r;

int main()
{ int x;

  read (x);
  r.a = 10+x;  r.b = false;  r.c = -10-x;
  if (x > 0)   r.b = true;
  else {}
  if (r.b)  print(r.a + r.c);
  else      print(1 - r.a - r.c);

  return 0;
}
