function cstar=linmachMatricial(w,x)
  vectorc = x*w;
  [_, res] = max(vectorc');
  cstar = res';
endfunction
