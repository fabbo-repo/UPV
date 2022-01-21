/* Beliefs */
adyacente(a, b).
adyacente(b, c).
adyacente(c, d).
adyacente(d, a).

localizado(robot, b).
localizado(papel_usado, a).
localizado(papel_usado, c).
localizado(papelera, d).


/* Goals */
!localizado(robot, d).

/* Events */	
+localizado(robot, X) : localizado(papel_usado, X)
			<- .print("papel cogido en ", X); 
			   -localizado(papel_usado, X); 
			   +llevando(papel_usado).

+localizado(robot, X) : localizado(papelera, X) &
				llevando(papel_usado)
			<- -llevando(papel_usado);
			   .print("todo el papel tirado a la papelera en ", X).

+!localizado(robot, X) : localizado(robot, X) &
				localizado(papel_usado, _) & adyacente(X,Z) 
			<- .print("mover de ", X, " a ", Z); 
			   -localizado(robot, X); 
			   +localizado(robot, Z); 
			   !localizado(robot, X).

+!localizado(robot, X) : localizado(robot, X) <- .print("Ha llegado a su destino").
 
+!localizado(robot, X) : localizado(robot, Y) &
				(not (X=Y)) & adyacente(Y,Z) 
			<- .print("mover de ", Y, " a ", Z); 
			   -localizado(robot, Y); 
			   +localizado(robot, Z); 
			   !localizado(robot, X).
