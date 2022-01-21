# c es la clase en la que se clasifica el prototipo i según k-NN
# Vi es el vector que contiene los índices de los m-NN del prototipo i
# ind es el vector de los prototipos que quedan tras aplicar Wilson n veces
# xl es un vector de Nx1 etiquetas
# k es el número de vecinos más cercanos
function [c]=knnV(Vi,ind,xl,k)
  # Vector que indica en binario si los elementos de Vi están en ind
  miembro = ismember(Vi,ind);
  # Índices de miembro que señala a los índices en Vi que sí están en ind
  YES = find(miembro==1);

  # Clasificar el prototipo i según sus k-NN
  # si hay empate elegir el de menor índice
  c = mode(xl'(Vi(YES(1:k))));
endfunction
