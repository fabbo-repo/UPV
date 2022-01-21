#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: pca+knn-eva.m <trdata> <trlabels> <tedata> <telabels> <k>\n")
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
k=str2num(arg_list{5});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

%
% HERE YOUR CODE
%
ind = wilson(X,xl,1);
X = X(ind,:);
xl = xl(ind,:);

# Obtenemos PCA
[m,W] = pca(X); 

# Proyectamos a k dimensiones el conjunto de entrenamiento y el conjunto de development
XP = X*W(:, 1:k);
YP = Y*W(:, 1:k);
[err] = knn(XP, xl, YP, yl, 1);
printf("Error con PCA: %f\n",err);
[err] = knn(X, xl, Y, yl, 1);
printf("Error sin PCA: %f\n",err);
