function [pXc]=gc(Pc,MUc,SIGMAc,X)
  #Probabilidad conjunta de X en la clase c
  # p(x,c) = P(c)*p(x|c)   #El sumatorio es 1
  
  inv = pinv(SIGMAc);
  Wc = (-1/2)*inv;
  wc = inv*MUc;
  w0 = log(Pc) - (1/2)*logdet(SIGMAc) - (1/2)*MUc'*inv*MUc;
  
  pXc = (sum((X*Wc).*X,2))' + (wc'*X') + w0;
  
endfunction
