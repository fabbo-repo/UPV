% Calcula la distancia L1
function D = L1dist(X,Y)
for i=1:rows(Y)
  D(:,i) = sum(abs(X-Y(i,:)), 2);
end
