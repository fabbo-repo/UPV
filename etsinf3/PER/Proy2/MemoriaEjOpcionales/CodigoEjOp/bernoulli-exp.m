#!/usr/bin/octave -qf

if (nargin!=6)
printf("Usage: bernoulli-exp.m <trdata> <trlabels> <umbrales> <epsilons> <%%trper> <%%dvper>\n")
# ./bernoulli-exp.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz 
#            "[0.2 0.3 0.4 0.5 0.6 0.7 0.8]" "[1e-8 1e-7 1e-6 1e-5 1e-4 1e-3 1e-2 1e-1 0.5]" 90 10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
umbral=str2num(arg_list{3});
epsilons=str2num(arg_list{4});
trper=str2num(arg_list{5});
dvper=str2num(arg_list{6});

load(trdata);
load(trlabs);

N=rows(X);
rand("seed",23); permutation=randperm(N);
X=X(permutation,:); xl=xl(permutation,:);

Ntr=round(trper/100*N);
Ndv=round(dvper/100*N);
Xtr=X(1:Ntr,:); xltr=xl(1:Ntr);
Xdv=X(N-Ndv+1:N,:); xldv=xl(N-Ndv+1:N);


for i=1:columns(epsilons)
    # Proyectamos a k dimensiones el conjunto de entrenamiento y el conjunto de development
    for u = umbral
        [edv] = bernoulli(Xtr, xltr, Xdv, xldv, u, epsilons(i));
        printf("%d %d %f\n",u,epsilons(i),edv);
    end
end
