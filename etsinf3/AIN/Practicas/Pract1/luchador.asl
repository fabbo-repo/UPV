//EJEMPLO LUCHADOR 

// 200 -> indicador de que es del equipo "Eje"
+flag(F): team(200)
  <-
  /* Crea N=3 puntos de control a una distancia D=100 de la ubicación F */
  .create_control_points(F,100,3,C);
  /* C es una lista de las posiciones de los puntos de control ([X,Y,Z])*/
  +control_points(C);
  //.wait(5000);
  .length(C,L);
  +total_control_points(L);
  +patrolling;
  +patroll_point(0);
  .print("Got control points:", C).


// Se ejecuta si estoy patrullando y soy aliado
+target_reached(T): patrolling & team(200)
  <-
  ?patroll_point(P);
  -+patroll_point(P+1);
  -target_reached(T).

/* P hace referencia al índice del punto de control al que se dirige el soldado */
+patroll_point(P): total_control_points(T) & P<T
  <-
  ?control_points(C); // Guarda en C el contenido de la primera creencia que haga matching
  .nth(P,C,A); // Guarda en A el elemento de la posición P en la lista C
  .goto(A). // Una vez llega a A se genera el evento +target_reached(A)
 // .print("Voy a Pos: ", A).

+patroll_point(P): total_control_points(T) & P==T
  <-
  -patroll_point(P);
  +patroll_point(0). // Cuando llegamos al último punto de control, volvemos al primero
 
 /*  En modo arena no hace falta disparar al enemigo  
  +enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
  <-
  .shoot(3,Position).
*/
  
  +friends_in_fov(ID,Type,Angle,Distance,Health,Position)
  <-
  .shoot(3,Position).
