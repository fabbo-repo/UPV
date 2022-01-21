#!/usr/bin/octave -qf

if (nargin!=7)
printf("Usage: pca+mixgaussian-exp.m <trdata> <trlabels> <K> <D> <alphas> <%%trper> <%%dvper>\n")
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
K=str2num(arg_list{3}); # Components
D=str2num(arg_list{4}); # Dimensions
alphas=str2num(arg_list{5});
trper=str2num(arg_list{6});
dvper=str2num(arg_list{7});

load(trdata);
load(trlabs);

N=rows(X);
seed=23; rand("seed",seed); permutation=randperm(N);
X=X(permutation,:); xl=xl(permutation,:);

Ntr=round(trper/100*N);
Ndv=round(dvper/100*N);
Xtr=X(1:Ntr,:); xltr=xl(1:Ntr);
Xdv=X(N-Ndv+1:N,:); xldv=xl(N-Ndv+1:N);

[m, W] = pca(Xtr);
Xtr = Xtr - m;
Xdv = Xdv - m;

printf("dimension;component;alpha;dv-err\n");

for ds = D
  # Se proyecta:
  XtrP = Xtr*W(:, 1:ds);
  XdvP = Xdv*W(:, 1:ds);
  for ks = K
    for alp = alphas
      [edv] = mixgaussian(XtrP,xltr,XdvP,xldv,ks,alp);
      printf("%f;%f;%e;%f\n",ds,ks,alp,edv);
    end
  end
end
