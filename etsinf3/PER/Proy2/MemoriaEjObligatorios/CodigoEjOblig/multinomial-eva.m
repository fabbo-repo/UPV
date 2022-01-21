#!/usr/bin/octave -qf

if (nargin!=5)
printf("Usage: multinomial-eva.m <trdata> <trlabels> <tedata> <telabels> <epsilon>\n")
# ./multinomial-eva.m train-images-idx3-ubyte.mat.gz train-labels-idx1-ubyte.mat.gz t10k-images-idx3-ubyte.mat.gz 
#            t10k-labels-idx1-ubyte.mat.gz 1e-10
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
epsilon=str2num(arg_list{5});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

[edv] = multinomial(X, xl, Y, yl, epsilon);
printf("Error para epsilon %d: %f\n",epsilon,edv(1));
