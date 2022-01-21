#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: multinomial-exp.m <trdata> <trlabels> <epsilons> <%%trper> <%%dvper>\n")
# ./multinomial-exp.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz 
#            "[1e-10 1e-9 1e-8 1e-7 1e-6 1e-5 1e-4 1e-3 1e-2 1e-1]" 90 10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
epsilons=str2num(arg_list{3});
trper=str2num(arg_list{4});
dvper=str2num(arg_list{5});

load(trdata);
load(trlabs);

N=rows(X);
rand("seed",23); permutation=randperm(N);
X=X(permutation,:); xl=xl(permutation,:);

Ntr=round(trper/100*N);
Ndv=round(dvper/100*N);
Xtr=X(1:Ntr,:); xltr=xl(1:Ntr);
Xdv=X(N-Ndv+1:N,:); xldv=xl(N-Ndv+1:N);

[edv] = multinomial(Xtr, xltr, Xdv, xldv, epsilons);
for i=1:columns(epsilons)
    printf("%d %f\n",epsilons(i),edv(i));
end
