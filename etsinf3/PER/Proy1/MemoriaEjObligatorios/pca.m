function[m,W] = pca(X)
  # Calculamos el vector media por filas
  m = mean(X)';
  # Restar a todos los datos el vector media
  Xm = X - m';
  # Calcular matriz de covarianza
  Mco = Xm'*Xm/rows(X);
  # Calcular los vectores y valores propios: VecP --> vectores propios y lambda--> valores propios
  [VecP, lambda] = eig(Mco);
  # Ordenar los vectores propios segun su valor propio de forma descendente
  # -> diag permite obtener el vector diagonal de valores propios
  [_,indices] = sort(diag(lambda), "descend"); 
  W = VecP(:,indices);
endfunction