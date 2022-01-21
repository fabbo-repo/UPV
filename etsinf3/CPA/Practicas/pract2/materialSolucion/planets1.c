// Computing with planets
// CPA, 2020, Universitat Politècnica de València

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 10000   
#define EPS 1e-6  
#define NGB_DST 150.0  // Neighborhood distance 

// 3D point
typedef struct {
  double x, y, z;
} Point3D;    

typedef struct {
  Point3D p; // position (million km)
  double m;  // mass (million kg)
  int ngb;   // number of neighbors
} Planet;

// Range for planet masses: [Mi, Ma]
#define Mi  1e18
#define Ma  1e26

// Random number in the range [i,a]
#define A(i,a) ( (i) + ((a)-(i))*rand()/RAND_MAX )

void generate_data( int n, Planet p[] )
{ int i;
  // Range for planet positions: [Xi, Xa]
  double Xi = 0, Xa = pow( n/3.7e-7, 1.0/3 );

  for (i=0; i<n; i++) {
    p[i].p.x = A(Xi,Xa);
    p[i].p.y = A(Xi,Xa);
    p[i].p.z = A(Xi,Xa);
    p[i].m = A(Mi,Ma);
    p[i].ngb = 0;
  }
}

int process_data( int n, Planet p[], Point3D *pcm )
{ int i, j, ngbi, k, max;
  double dx, dy, dz,d, m;
  Point3D cm; // center of mass

  cm.x = cm.y = cm.z = 0; m = 0;
  for (i=0; i<n; i++) {
    // Accumulate mass and weighted position to compute the center of mass
    m += p[i].m;
    cm.x += p[i].m*p[i].p.x;
    cm.y += p[i].m*p[i].p.y;
    cm.z += p[i].m*p[i].p.z;

    // Update count of neighboring planets 
    ngbi = 0;
    for (j=i+1; j<n; j++) {
      // Compute distance between planet i and planet j
      dx = p[i].p.x - p[j].p.x;
      dy = p[i].p.y - p[j].p.y;
      dz = p[i].p.z - p[j].p.z;
      d = sqrt(dx*dx + dy*dy + dz*dz);
      if ( d < NGB_DST ) {
        // Planets i and j are neighbors. Update number of neighbors
        // for both planets
        ngbi++;
        p[j].ngb++;
      }
    }
    p[i].ngb += ngbi;
  }

  // Finish computation of the center of mass
  if ( m > EPS ) { cm.x /= m; cm.y /= m; cm.z /= m; }

  // Find the planet with most neighbors
  k = 0; max = -1;
  for (i=0; i<n; i++) {
    if ( p[i].ngb > max ) {
      max = p[i].ngb; k = i;
    }
  }

  *pcm = cm;
  return k;
}

int main( int argc, char *argv[] )
{ Planet *p; 
  int n=N, k;  
  Point3D cm;   

  if ( argc > 1 ) {
    n = atoi(argv[1]);
    if ( n < 10 ) n = 10;
  }

  p = malloc(n*sizeof(*p));
  if ( p == NULL ){
    fprintf( stderr, "ERROR: Not enough memory.\n" );
    return 1;
  }

  generate_data( n, p );

  /* Ejercicio 1: Mostrar tiempo empleado en process_data y mostrar cantidad de planetas */
  double t1 = omp_get_wtime();
  k = process_data( n, p, &cm );
  double t2 = omp_get_wtime();
  printf("Tiempo de ejecución empleado en process_data: %f\n", t2-t1);
  printf("Cantidad de planetas: %d\n", n);
  
  printf( "The center of mass is in ( %g, %g, %g ).\n",
      cm.x, cm.y, cm.z );
  printf( "The planet with most neighbors is %d (%d neighbors).\n",
      k, p[k].ngb );

  free(p);

  return 0;
}

