# X es el conjunto de prototipos
# xl es el vector de etiquetas de dichos prototipos
# k es el número de vecinos más cercanos a considerar para la clasificación
function [ind] = wilson(X,xl,k)
  # Se inicializa a los índices de los prototipos en orden creciente
  ind = [1:rows(X)];
  # V es el vector que contiene los índices de los m-NN de cada prototipo en X
  V = mnn(X,xl,min(100,rows(X)-1)); # consideramos almacenar hasta 100-NN
  
  # Repetimos el proceso de clasificación por k-NN hasta que ninguno se clasifique mal
  error=true;
  while(error)
    error=false;
    # Para cada prototipo que aún no haya sido eliminado por Wilson
    # recorrido en orden creciente de índices
    for i=ind
      # Clasificar el prototipo i
      c = knnV(V(:,i),ind,xl,k);
      # Si el clasificador k-NN no acierta, eliminar este prototipo ruidoso 
      if(c != xl(i))
        ind = setdiff(ind,i); error = true;
      endif
    endfor
  endwhile
endfunction
