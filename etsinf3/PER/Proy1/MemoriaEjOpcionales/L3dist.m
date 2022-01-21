% Calcula la distancia L3
function D = L3dist(X,Y)
for i=1:rows(Y)
  D(:,i) = sum(abs(X-Y(i,:)).^3, 2); 
  % No se realiza la raiz cúbica puesto que solo vemos la mayor distancia
end
