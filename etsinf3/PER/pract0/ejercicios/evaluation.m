#!/usr/bin/octave -qf

# ./evaluation.m trimages.mat.gz trlabels.mat.gz [0.1,0.01,0.001] [1.0,10.0,100.0] 200 5 5
if (nargin!=7)
printf("Usage: experiment.m <trdata> <trlabels> <as> <bs> <maxK> <%%tr> <%%dv>\n")
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
as=str2num(arg_list{3});
bs=str2num(arg_list{4});
K=str2num(arg_list{5});
trper=str2num(arg_list{6});
dvper=str2num(arg_list{7});

# Loading matrices
load(trdata);
load(trlabs);

output_precision(2);

[N,D]=size(X); 
ll=unique(xl); C=numel(ll);
rand("seed",23); permutation=randperm(N);
X=X(permutation,:); xl=xl(permutation,:);

% Selecting a percentage of the validating data
Ndv=round(dvper/100*N);
Y=X(N-Ndv:N,:); 
yl=xl(rows(xl)-Ndv:rows(xl));
% Selecting a percentage of the training data
Ntr=round(trper/100*N);
X=X(1:Ntr,:); 
xl=xl(1:Ntr);

M=rows(Y);

printf("#      a        b   E   k Ete Ete (%%)    Ite (%%)\n");
printf("#------- -------- --- --- --- ------- ----------\n");
for a=as
  for b=bs
    [w,E,k]=perceptron([X xl],b,a,K); rl=zeros(M,1);
    for n=1:M rl(n)=ll(linmach(w,[1 Y(n,1:D)]')); end
    [nerr m]=confus(yl,rl);
    m=nerr/M; s=sqrt(m*(1-m)/M); r=1.96*s;
    if (m-r)<0 lowr=0; else lowr=m-r; end
    highr=m+r;
    printf("%8.1f %8.1f %3d %3d %3d    %3.1f [%3.1f, %3.1f]\n",a,b,E,k,nerr,m*100,lowr*100,highr*100);
  end
end
