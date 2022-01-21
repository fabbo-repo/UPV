include "rect10.dzn";

% Variable que contiene número de rectangulos
%par int: NR = 15;

% Variable que contiene la dimensión minima de la base
var int: D;

% Vector que contiene el Alto, se pide como parámetro
%array[1..NR] of par int: Alto;
% Vector que contiene el Ancho, se pide como parámetro
%array[1..NR] of par int: Ancho;
% Vector que contiene posiciones en X (extremo inferior izquierdo)
array[1..NR] of var 0..100: PosX;
% Vector que contiene posiciones en Y (extremo inferior izquierdo)
array[1..NR] of var 0..100: PosY;

% Restricciones de solapamiento en X y en Y:
constraint forall (i,j in 1..NR-1 where i!=j) (
    (PosX[j]>=PosX[i]+Ancho[i]) \/ (PosX[i]>=PosX[j]+Ancho[j]) 
    \/ (PosY[i]>=PosY[j]+Alto[j]) \/ (PosY[j]>=PosY[i]+Alto[i])
  );
% Restriccion rectangulo 15:
constraint forall(i in 1..NR-1)(
    (PosX[NR]>=PosX[i]+Ancho[i] \/ PosX[i]>=PosX[NR] + Ancho[NR] 
    \/ PosY[i] >= PosY[NR] + Alto[NR] \/ PosY[NR] >= PosY[i] + Alto[i]) 
    /\ (PosX[i] >= PosX[NR] + Alto[NR] \/ PosX[NR] >= PosX[i] + Ancho[i] 
    \/ PosY[NR] >= PosY[i] + Alto[i] \/ PosY[i] >= PosY[NR] + Ancho[NR])
);
  
% Restricciones de Anchura y Altura:
constraint forall (i in 1..NR-1) (
    PosY[i]+Alto[i] <= D /\ PosX[i]+Ancho[i] <= D
  );
constraint ((PosX[NR]+Ancho[NR]<=D /\ PosY[NR]+Alto[NR]<=D) 
        \/ (PosX[NR]+Alto[NR]<=D /\ PosY[NR]+Ancho[NR]<=D));

solve minimize(D*D);

% Salida:
output["Posiciones en X = ", show(PosX), "\n","Posiciones en Y = ",show(PosY), "\n","D = ",show(D), "\n"];