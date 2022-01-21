function cstar=linmach(w,x)
  vectorc = (x*w)'
  [maximos, pos] = max(vectorc)
  cstar = pos'
endfunction
