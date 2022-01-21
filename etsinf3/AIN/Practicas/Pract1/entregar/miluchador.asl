// 200 -> indicador de que es del equipo "Eje"
+flag(F): team(200)
  <-
  ?position(POS); 
  .create_control_points(POS,100,1,C);
  .nth(0,C,A); // Guarda en A el elemento de la posición 0 en la lista C
  .goto(A).


+pack_taken(Type, N): Type == medic & needhealing & goingpack
  <-
  -goingpack;
  //.print("Medic taken");
  -needhealing.
+pack_taken(Type, N): Type == medic & needhealing
  <-
  //.print("Medic taken");
  -needhealing.


+pack_taken(Type, N): Type == fieldops & outofammo & goingpack
  <-
  //.print("Ammo taken");
  -goingpack;
  -outofammo.
+pack_taken(Type, N): Type == fieldops & outofammo
  <-
  //.print("Ammo taken");
  -outofammo.


+target_reached(T): goingpack
  <-
  ?base(X);
  -goingpack;
  .create_control_points(X,8,1,C);
  .nth(0,C,A); // Guarda en A el elemento de la posición 0 en la lista C
  //.print("Looking for packs!");
  .goto(A).
+target_reached(T): outofammo | needhealing
  <-
  ?base(X);
  .create_control_points(X,8,1,C);
  .nth(0,C,A); // Guarda en A el elemento de la posición 0 en la lista C
  //.print("Looking for packs!");
  .goto(A).
+target_reached(T): shooting
  <-
  -shooting;
  ?position(POS);
  .create_control_points(POS,100,1,C);
  .nth(0,C,A); // Guarda en A el elemento de la posición 0 en la lista C
  //.print("Enemy lost, going to: ", A);
  .goto(A).
+target_reached(T)
  <-
  ?position(POS);
  .create_control_points(POS,100,1,C);
  .nth(0,C,A); // Guarda en A el elemento de la posición 0 en la lista C
  .goto(A).


+outofammo
  <-
  ?base(X);
  //.print("Going to base for ammo");
  .goto(X).
+needhealing
  <-
  ?base(X);
  //.print("Going to base for healing");
  .goto(X).


+ammo(Y): not outofammo & Y < 1
  <-
  //.print("Run out of ammo");
  +outofammo.
+health(X): X < 60 & not needhealing
  <-
  //.print("Need healing!");
  +needhealing.


+packs_in_fov(ID,Type,Angle,Distance,Health,Position): 
  Type == 1001 & needhealing & not goingpack
  <-
  +goingpack;
  //.print("Medic Pack seen");
  .goto(Position).
+packs_in_fov(ID,Type,Angle,Distance,Health,Position): 
  Type == 1002 & outofammo & not goingpack
  <-
  +goingpack;
  //.print("Ammo Pack seen");
  .goto(Position).


+friends_in_fov(ID,Type,Angle,Distance,Health,Position): 
	not (outofammo | needhealing) & not shooting & Health <= 50
  <-
  +shooting;
  .goto(Position);
  .shoot(3,Position).
+friends_in_fov(ID,Type,Angle,Distance,Health,Position): 
  not outofammo
  <-
  .shoot(3,Position).
