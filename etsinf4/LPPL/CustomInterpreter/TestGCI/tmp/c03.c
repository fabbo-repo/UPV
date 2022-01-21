// Ejemplo de manipulacion de vectores
// Devuelve la cuenta inversa de 9 a 0 (inclusive)
//------------------------------------------------
int a[10];

int main()
{ int i;

  i = 0;
  while (i < 10) { a[i] = i;  i = i+1;}
  i = 9;
  while (i >= 0) { print(a[i]); i = i-1;} 

  return 0;
}
