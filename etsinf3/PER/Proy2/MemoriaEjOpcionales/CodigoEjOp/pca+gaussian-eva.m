#!/usr/bin/octave -qf

if (nargin!=6)
printf("Usage: pca+gaussian-eva.m <trdata> <trlabels> <tedata> <telabels> <k> <alpha>\n")
# ./pca+gaussian-eva.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz t10k-images-idx3-ubyte.mat.gz 
#            t10k-labels-idx1-ubyte.mat.gz 500 1e-4
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
k=str2num(arg_list{5});
alpha=str2num(arg_list{6});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

# Obtenemos PCA
[m,W] = pca(X); 

# Proyectamos a k dimensiones el conjunto de entrenamiento y el conjunto de development
XP = X*W(:, 1:k);
YP = Y*W(:, 1:k);
[err] = gaussian(XP, xl, YP, yl, alpha);
printf("Error con PCA: %f\n",err);