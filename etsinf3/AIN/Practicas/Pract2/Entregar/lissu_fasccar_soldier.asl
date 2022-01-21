//TEAM_AXIS
+flag(F): team(200)
  <-
  .get_backups.

//-----------------------------------------------------
+myBackups(M)
  <-
  .length(M,L); // En M no se incluye este soldado
  +soldadosTotales(M);
  +soldadosPendientes(L);
  ?position(P); ?name(N);
  +mejorPosicion(P); +mejorSoldado(N);
  .send(M, tell, saveMyPos(P)).
//-----------------------------------------------------
+saveMyPos(SM) [source(S)] //Agente S en la pos P
  <-
  .wait(1000); 
  // Espera antes de consultar las creencias en caso de que estas 
  // no se hayan añadido todavía
  ?soldadosPendientes(SP); ?mejorPosicion(MP);
  ?flag(F); .mejorPos(MP, SM, F, I);
  if(I == 2){
    -+mejorPosicion(SM);
    -+mejorSoldado(S);
  }
  -+soldadosPendientes(SP-1).
//-----------------------------------------------------
+soldadosPendientes(SP): SP==0
<-
  -soldadosPendientes(SP); ?mejorSoldado(MS); ?mejorPosicion(MP);
  +liderEscogido(MS); -mejorSoldado(MS); -mejorPosicion(MP).
//-----------------------------------------------------
+liderEscogido(LE): name(N) & N==LE
  <-
  .register_service("lider"); //Para que los fieldops y medics sepan quién es el líder, los soldiers lo saben
  ?flag(F); .goto(F).
//-----------------------------------------------------
+liderEscogido(LE): name(N)
  <-
  .giveRing([N], [LE], GR); +ring(GR);
  ?flag(F); .givePositionSoldier(GR,F,GPS);
  
  +control_points(GPS); .length(GPS,L);
  .randomPos(L-1,RP);
  +total_control_points(L);
  +patroll_point(RP).

//-----------------------------------------------------
+munition(POS): soldierNeedAmmo(S)
  <-
  -soldierNeedAmmo(S);
  .send(S, tell, ammoAt(POS)).
+healing(POS): soldierNeedHealing(S)
  <-
  -soldierNeedHealing(S);
  .send(S, tell, healingAt(POS)).

//-----------------------------------------------------
+outofammo: liderEscogido(LE)
  <-
  .send(LE, tell, sneedammo).
+ammoAt(Pos)
  <-
  .print("Yendo a por municion");
  .goto(Pos).
+needhealing: liderEscogido(LE)
  <-
  .send(LE, tell, sneedhealing).
+healingAt(Pos)
  <-
  .print("Yendo a por medicina");
  .goto(Pos).

//-----------------------------------------------------
+sneedammo [source(S)]
  <-
  .get_fieldops; .wait(1000);
  ?myFieldops(F); .length(F, L);
  if(not (L == 0)){ 
    +soldierNeedAmmo(S); .nth(0,F,A);
    .send(A, tell, ayuda);
  }
  .print("Lider pidiendo ayuda").
+sneedhealing [source(S)]
  <-
  .get_medics; .wait(1000);
  ?myMedics(M); .length(M, L);
  if(not (L == 0)){ 
    +soldierNeedHealing(S); .nth(0,M,A);
    .send(A, tell, ayuda);
  }
  .print("Lider pidiendo ayuda").
//-----------------------------------------------------
+ammo(Y): not outofammo & Y < 3
  <-
  +outofammo.
+health(X): X < 80 & not needhealing
  <-
  +needhealing.

//-----------------------------------------------------
+pack_taken(Type, N): Type == medic & needhealing & goingpack & healingAt(T)
  <-
  -goingpack; -healingAt(T); -needhealing.
+pack_taken(Type, N): Type == medic & needhealing
  <-
  -needhealing.
+pack_taken(Type, N): Type == fieldops & outofammo & goingpack & ammoAt(T)
  <-
  -goingpack; -outofammo.
+pack_taken(Type, N): Type == fieldops & outofammo
  <-
  -outofammo.

//-----------------------------------------------------
+enemyAt(Position)
  <-
  .look_at(Position).

//-----------------------------------------------------
+shootPos(Position): not (healingAt(T1) | ammoAt(T2))
  <-
  .goto(Position).

//-----------------------------------------------------
+patroll_point(P): total_control_points(T) & P<T
  <-
  ?control_points(C); .nth(P,C,A);
  .goto(A).
+patroll_point(P): total_control_points(T) & P==T
  <-
  -patroll_point(P); +patroll_point(0).
//-----------------------------------------------------
+target_reached(T): goingpack
  <-
  -goingpack; +target_reached(T).
+target_reached(T): patroll_point(P)
  <-
  -+patroll_point(P+1); -target_reached(T).

//-----------------------------------------------------
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

//-----------------------------------------------------
+enemies_in_fov(ID,Type,Angle,Distance,Health,Position):
  liderEscogido(LE) & name(N) & N==LE & not enemyNew(Position) 
  & not (healingAt(T1) | ammoAt(T2))
  <-
  .look_at(Position); .shoot(3,Position); +enemyNew(Position);
  ?soldadosTotales(ST); .send(ST, tell, shootPos(Position)).

+enemies_in_fov(ID,Type,Angle,Distance,Health,Position):
  liderEscogido(LE) & name(N) & not (N==LE) & not enemyNew(Position)
  & not (healingAt(T1) | ammoAt(T2))
  <-
  .stop; .look_at(Position);
  .shoot(3,Position); +enemyNew(Position);
  .send(LE, tell, enemyAt(Position)).
  
+enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
  <-
  .shoot(3,Position).

