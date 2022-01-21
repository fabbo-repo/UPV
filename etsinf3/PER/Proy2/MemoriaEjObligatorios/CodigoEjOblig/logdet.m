function v = logdet(X)
    lambda = eig(X);
    if any(lambda<=0)
        v = log(realmin);
    else
        v = sum(log(lambda));
    endif
endfunction