include "rect5.dzn";

% Variable que contiene número de rectangulos
%par int: NR = 5;

% Variables que contienen la dimensión minima de la base
var int: DX;
var int: DY;

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
    (PosX[j]>=PosX[i]+Ancho[i]) \/ (PosX[i]>=PosX[j]+Ancho[j]) 
    \/ (PosY[i]>=PosY[j]+Alto[j]) \/ (PosY[j]>=PosY[i]+Alto[i])
  );
  
% Restricciones de Anchura y Altura:
constraint forall (i in 1..NR) (
    PosY[i]+Alto[i] <= DY /\ PosX[i]+Ancho[i] <= DX
  );
  
solve minimize(DX*DY);

% Salida:
output["Posiciones en X = ", show(PosX), "\n","Posiciones en Y = ",show(PosY), "\n","DX*DY = ",show(DX*DY), "\n"];