#!/usr/bin/octave -qf
if (nargin!=3) 
  printf("Usage: ./experiment.m <data> <alphas> <bes>\n");
  exit(1);
end

arg_list=argv();
data=arg_list{1};
as=str2num(arg_list{2}); % as = alphas
bs=str2num(arg_list{3}); % bs = betas

load(data);  
[N,L]=size(data); % N -> filas (cantidad de datos en la muestra), L -> columnas
D=L-1; % D -> cantidad de carácteristicas de cada dato

ll = unique(data(:, L)); % ll -> clases a las que pertenecen 
C=numel(ll); % cantidad de clases
rand("seed",23);  
data=data(randperm(N),:);

NTe = round(.7*N); % 70% es usado para entrenamiento  
M=N-NTe;  % M -> datos totales - datos para entrenamiento -> datos para test 
test=data(NTe+1:N, :);

printf("#       a        b     E     k   Ete   Ete (%%)     Ite (%%)\n");
printf("#-------- -------- ----- ----- ----- --------- -----------\n");
    
for a = as
  for b = bs
    [w,E,k] = perceptron(data(1:NTe, :), b, a);  
    r1 = zeros(M, 1);
    
    for n=1:M
      r1(n) = ll(linmach(w, [1, test(n, 1:D)]'));
    end
    [nerr, m] = confus(test(:,L), r1); % nerr -> numero de errores

    pe = nerr/M;  % Probabilidad de error
    s = sqrt(pe*(1-pe)/M);
    r= 1.96*s;  % Intervalo del 95%

    ite1 = (pe-r); ite2 = (pe+r); % Intervalo de confianza

    if (ite1 < 0) ite1 = 0; end
    if (ite2 > 1) ite2 = 1; end
    
    printf("%9.1f %8.1f %5d %5d %5d %8.1f   [%.1f, %.1f]\n", 
        a, b, E, k, nerr, pe*100, ite1*100, ite2*100);
  end
end