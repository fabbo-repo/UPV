#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: pca+knn-exp.m <trdata> <trlabels> <ks> <%%trper> <%%dvper>\n")
# ./pca+knn-exp.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz 
#            "[1 2 5 10 20 50 100 200 500]" 90 10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
ks=str2num(arg_list{3});
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

%
% HERE YOUR CODE
% 
ind = wilson(Xtr,xltr,1);
Xtr = Xtr(ind,:);
xltr = xltr(ind,:);
[err] = knn(Xtr, xltr, Xdv, xldv, 1);
printf("Error sin PCA y wilson: %f\n",err);

# Obtenemos PCA
[m,W] = pca(Xtr); 

for k = ks
    # Proyectamos a k dimensiones el conjunto de entrenamiento y el conjunto de development
    XtrP = Xtr*W(:, 1:k);
    XdvP = Xdv*W(:, 1:k);
    [err] = knn(XtrP, xltr, XdvP, xldv, 1);
    printf("%d %f\n",k,err);
end
