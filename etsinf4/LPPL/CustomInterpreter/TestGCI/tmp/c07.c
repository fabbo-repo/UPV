// Criba de Eratostenes: calcula los numeros primos menores 
// que un cierto numero  1 < n < 150.
//---------------------------------------------------------
bool a[150];

int main()
{ int max;     // Numero maximo para buscar
  int n;       // Siguiente numero primo
  int i;
  bool ok;

  // Comprobacion de que es un numero admisible
  ok = false;
  while (! ok) {
    read(max);
    if ((max > 1) && (max < 150)) ok = true; else {}
  }
  // Inicializacion del vector de posible primos
  i = 2;
  while (i <= max) { a[i] = true;  i = i+1; }
  
  // Criba de Earatostenes
  n = 2;  ok = false;
  while (! ok) {
    // Eliminacion de los multiplos de "n"
    i = 2;
    while ((i * n) <= max) { a[i * n] = false;  i = i+1; } 
    // Busqueda del siguiente primo
    i = n + 1;
    while (! a[i] && (i <= max)) { i = i+1; }
    // Control del fin (n * n > max)
    if ((i * i) <= max) n = i;
    else  ok = true;
  }

  // visualizacion de los primos menores que "max"
  i = 2;
  while (i <= max) {
    if (a[i]) print(i); else {}
    i = i+1;
  }
  
  return 0;
}
