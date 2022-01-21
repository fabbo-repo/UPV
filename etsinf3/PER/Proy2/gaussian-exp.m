#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: gaussian-exp.m <trdata> <trlabels> <alphas> <%%trper> <%%dvper>\n")
# ./gaussian-exp.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz 
#            "[1e-9 1e-8 1e-7 1e-6 1e-5 1e-4 1e-3 1e-2 1e-1 9e-1]" 90 10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
alphas=str2num(arg_list{3});
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

[edv] = gaussian(Xtr, xltr, Xdv, xldv, alphas);
for i=1:columns(alphas)
    printf("%d %f\n",alphas(i),edv(i));
end
