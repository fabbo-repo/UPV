function [edv]=gaussian(Xtr,xltr,Xdv,xldv,alphas)
  labsTr = unique(xltr); # Las clases existentes, ordenadas y sin repetidas.
  numTr = numel(labsTr); # Numero de clases diferentes en xltr
  numDv = numel(unique(xldv));
  
  # Probabilidad de cada clase
  Pc = zeros(1,numTr);
  
  [N,D] = size(Xtr); # N filas, D columnas
  mu = zeros(D,numTr); # Las D filas representan los Xd, cada columna representa una clase
  sigma = {}; # 'numTr' matrices DxD
  
  # P(X,C)
  pTr = zeros(rows(Xtr),numTr);
  pDv = zeros(rows(Xdv),numDv);
  
  for c=1:numTr
    ind = find(labsTr(c)==xltr); # Indices de las muestras de c

    # Probabilidad a priori P(c)=Nc/N
    Pc(c) = numel(ind)/N;
    
    # Medias para cada clase
    Xn = Xtr(ind,:); # Muestras de la clase c
    mu(:,c) = mean(Xn,1)'; # Suma por columnas, dividido por Nc
    
    # Matriz de covarianza para cada clase
    Xm = Xn - mu(:,c)';
    sigma{c} = (Xm'*Xm)/numel(ind);
  endfor
  
  etr=[]; edv=[];
  for a=alphas
    for c=1:numTr
      sigmaC = a*sigma{c} + (1 - a)*eye(size(sigma{c}));
      # Probabilidad conjunta de X con C
      pDv(:,c) = gc(Pc(c),mu(:,c),sigmaC,Xdv);
    endfor
    
    # Error del conjunto de validacion
    [v etiq] = max(pDv');
    error = xldv!=(etiq'-1);
    edv = [edv; sum(error)/rows(error)*100];
  endfor
  
endfunction