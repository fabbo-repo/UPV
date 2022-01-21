function [edv]= bernoulli(X,xltr,Y,yldv,umbral,epsilons)
  # Se procede a obtener 1 y 0 dependiendo del umbral
  Xtr=X; Xdv=Y;
  maxX=max(max(X)); minX=min(min(X));
  Xtr=(Xtr>(minX+(maxX-minX)*umbral)); # La umbral del rango entre el m�ximo y el m��nimo
  maxY=max(max(Y)); minY=min(min(Y));
  Xdv=(Xdv>(minY+(maxY-minY)*umbral));
  
  # Dimension de los datos
  D = columns(X);
  
  # N� etiquetas del conjunto de entrenamiento 
  C = numel(unique(xltr)');
  
  edv = [];
  for e=epsilons
    priori = []; 
    pcs = zeros(D,numel(C));
    
    for c=1:C 
      # 0-9
      ind = find(xltr==c-1);
      Nc = rows(ind);
      
      priori = [priori; Nc/rows(X)];
      pc = sum(Xtr(ind,:))/Nc;
    
      # Aplicamos Truncamiento Simple con el valor de epsilon 
      ind = find(pc < e);
      pc(ind) = e;
      ind = find(pc > 1-e);
      pc(ind) = 1-e;
      
      # Vectores de probabilidades de cada clase
      pcs(:,c) = pc;
    endfor
    
    # Clasificaci�n:
    sumPcd = sum(log(1-pcs))'; # Pcd es cada componente en pc
    wC0 = log(priori)+sumPcd; 
    
    wC = log(pcs)'-log(1-pcs)';
    res = wC*Xdv' + wC0;
    [ig, etiq] = max(res);
    etiq = (etiq-1)';
    edv = [edv, sum(etiq != yldv)/rows(Xdv)*100];
  endfor
endfunction