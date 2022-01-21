#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX

int primo(Entero_grande n)
{
  volatile int p;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);

    int id,inc;
    #pragma omp parallel private(id, i)
    {
      id = omp_get_thread_num();
      inc = omp_get_num_threads();
      for (i = 3+2*id; p && i <= s; i += 2*inc)
        if (n % i == 0) p = 0;
    } 
  }

  return p;
}

int main()
{
  Entero_grande n;

  double t1 = omp_get_wtime();
  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }
  double t2 = omp_get_wtime();
   
  printf("Tiempo de ejecución: %f\n", t2-t1);
   int iam;
   #pragma omp parallel
   iam = omp_get_num_threads();
   printf("Numero de hilos: %d\n", iam);

  printf("El mayor primo que cabe en %lu bytes es %llu.\n",
         sizeof(Entero_grande), n);

  return 0;
}
