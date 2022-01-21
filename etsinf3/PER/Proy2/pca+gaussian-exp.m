#!/usr/bin/octave -qf

if (nargin!=6)
printf("Usage: pca+gaussian-exp.m <trdata> <trlabels> <ks> <alphas> <%%trper> <%%dvper>\n")
# ./pca+gaussian-exp.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz 
#            "[1 2 5 10 20 50 100 150 175 200 500]" "[1e-5 1e-4 1e-3]" 90 10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
ks=str2num(arg_list{3});
alphas=str2num(arg_list{4});
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

# Obtenemos PCA
[m,W] = pca(Xtr);

for i=1:columns(alphas)
    # Proyectamos a k dimensiones el conjunto de entrenamiento y el conjunto de development
    for k = ks
        XtrP = Xtr*W(:, 1:k);
        XdvP = Xdv*W(:, 1:k);
        [edv] = gaussian(XtrP, xltr, XdvP, xldv, alphas(i));
        printf("%d %d %f\n",k,alphas(i),edv);
    end
end
