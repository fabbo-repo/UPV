function cstar=linmach2(w,x)
  vectorc = x'*w;
  [_, cstar] = max(vectorc);
endfunction
