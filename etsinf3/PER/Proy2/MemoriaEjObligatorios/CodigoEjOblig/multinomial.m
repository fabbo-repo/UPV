function [edv]=multinomial(Xtr,xltr,Xdv,xldv,epsilons)
  # Etiquetas del conjunto de entrenamiento 
  C = unique(xltr)';
  pX = []; pC = []; 
  for c=C # Para cada clase se calcula el vector de las proporciones
    suma = sum( Xtr(find(xltr==c),:) ); pAuX = suma';
    pX =[pX, pAuX / sum(suma,2)];
    pC = [pC; rows(find(xltr==c)) / rows(xltr)];
  endfor
  wC0 = log(pC);
  E = epsilons; edv=[];
  for e = E
    # Aplicamos LaPlace con el valor de epsilons 
    newPX = pX + e; # Sumo la epsilon a todos los parámetros 
    for r = 1:columns(pX) # Renormalizamos
      newPX(:,r) = newPX(:,r)/sum(newPX(:,r));
    endfor
    # Clasificación: 
    wC = log(newPX)'; 
    res = wC*Xdv' + wC0;
    [v,etiq] = max(res);
    etiq = (etiq-1)';
    edv = [edv, sum(etiq != xldv)/rows(Xdv)*100];
  endfor
endfunction