include "rect15.dzn";
% Variable que contiene número de rectangulos
%par int: NR = 15;

% Variable que contiene la dimensión minima de la base (100 para aproximar)
var int: D;

% Vector que contiene el Alto, se pide como parámetro
%array[1..NR] of par int: Alto;
% Vector que contiene el Ancho, se pide como parámetro
%array[1..NR] of par int: Ancho;
% Vector que contiene posiciones en X (extremo inferior izquierdo)
array[1..NR] of var 0..200: PosX;
% Vector que contiene posiciones en Y (extremo inferior izquierdo)
array[1..NR] of var 0..200: PosY;

% Restricciones de solapamiento en X y en Y:
constraint forall (i,j in 1..NR where i!=j) (
    (PosX[j]>=PosX[i]+Ancho[i]) \/ (PosX[i]>=PosX[j]+Ancho[j]) \/ (PosY[i]>=PosY[j]+Alto[j]) \/ (PosY[j]>=PosY[i]+Alto[i])
  );
  
% Restricciones de Anchura y Altura:
constraint forall (i in 1..NR) (
    PosY[i]+Alto[i]<=D /\ PosX[i]+Ancho[i]<=D
  );

% Restriccion del Rectangulo 4:
constraint PosY[4]+Alto[4]==D;

solve minimize(D*D);

% Salida:
output["Posiciones en X = ", show(PosX), "\n","Posiciones en Y = ",show(PosY), "\n","D = ",show(D), "\n"];