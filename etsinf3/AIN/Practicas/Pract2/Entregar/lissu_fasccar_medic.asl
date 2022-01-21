//TEAM_AXIS

+flag(F): team(200) 
  <-
  .create_control_points(F,30,1,C);
  .nth(0,C,A);
  .goto(A).

+ayuda [source(S)]
  <-
  ?position(POS);
  .send(S, tell, healing(POS));
  .print("Soltando botiquin");
  .cure.

+target_reached(T): team(200) 
  <-
  ?flag(F);
  .create_control_points(F,30,1,C);
  .nth(0,C,A);
  .goto(A).

+lider(ML): enemyNew(Position)
  <-
  -enemyNew(Position);
  .send(ML, tell, enemyAt(Position)).

+enemies_in_fov(ID,Type,Angle,Distance,Health,Position):
  not enemyNew(Position)
  <-
  .stop;
  .look_at(Position); .shoot(3,Position);
  +enemyNew(Position); .get_service("lider").
  
+enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
  <-
  .stop;
  .look_at(Position);
  .shoot(3,Position).