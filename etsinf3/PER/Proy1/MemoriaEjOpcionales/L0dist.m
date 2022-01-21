% Calcula la distancia L0
function D = L0dist(X,Y)
for i=1:rows(Y)
  D(:,i) = max(abs(X-Y(i,:))')';
end
