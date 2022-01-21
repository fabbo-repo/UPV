#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: gaussian-eva.m <trdata> <trlabels> <tedata> <telabels> <alpha>\n")
# ./gaussian-eva.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz t10k-images-idx3-ubyte.mat.gz 
#            t10k-labels-idx1-ubyte.mat.gz 1e-9
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
alpha=str2num(arg_list{5});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

[edv] = gaussian(X, xl, Y, yl, alpha);
printf("Error para alpha %d: %f\n",alpha,edv(1));
