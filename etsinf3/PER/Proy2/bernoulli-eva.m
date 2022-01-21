#!/usr/bin/octave -qf

if (nargin!=6)
printf("Usage: bernoulli-eva.m <trdata> <trlabels> <tedata> <telabels> <umbral> <epsilon>\n")
# ./bernoulli-eva.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz t10k-images-idx3-ubyte.mat.gz 
#            t10k-labels-idx1-ubyte.mat.gz 0.5 1e-4
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
umbral=str2num(arg_list{5});
epsilon=str2num(arg_list{6});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

[err] = bernoulli(X, xl, Y, yl, umbral, epsilon);
printf("Error con PCA: %f\n",err);