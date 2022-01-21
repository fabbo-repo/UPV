function [nerr]=confus2(truelabs,recolabs)
  truelabs=reshape(truelabs,numel(truelabs),1);
  recolabs=reshape(recolabs,numel(recolabs),1);

  # Filas de truelabs
  N=rows(truelabs);                  
  
  a=numel( find( truelabs([1:N])==recolabs([1:N]) ) );
  
  nerr=N-a;
endfunction
