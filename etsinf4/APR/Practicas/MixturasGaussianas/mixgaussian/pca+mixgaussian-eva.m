#!/usr/bin/octave -qf

if (nargin!=7)
printf("Usage: pca+mixgaussian-exp.m <trdata> <trlabels> <tedata> <telabels> <K> <D> <alphas>\n")
exit(1);
end;

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
K=str2num(arg_list{5}); # Components
D=str2num(arg_list{6}); # Dimensions
alphas=str2num(arg_list{7});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

M = rows(Y);

[m, W] = pca(X);
X = X - m;
Y = Y - m;

printf("dimension;component;alpha;dv-err;intervalos\n");

for ds = D
  # Se proyecta:
  XP = X*W(:, 1:ds);
  YP = Y*W(:, 1:ds);
  for ks = K
    for alp = alphas
      [edv] = mixgaussian(XP,xl,YP,yl,ks,alp);
      m=edv/ 100;
      s=sqrt(m*(1-m)/M);
      r=1.96*s;
      printf("%f;%f;%e;%f;[%.3f,%.3f]\n",ds,ks,alp,edv,(m-r)*100,(m+r)*100);
    end
  end
end
