#!/usr/bin/octave -qf

if (nargin!=9)
    printf("Usage: svm-exp.m <trdata> <trlabels> <D> <cs> <ts> <ds> <gam> <%%trper> <%%dvper>\n%d\n",nargin)
    exit(1);
end;

# ./svm-exp2.m mnist/trainX.mat.gz mnist/trainxl.mat.gz [50,100,200] [1,10,100] [0,1,2,3] [1,2,3,4,5] [1e-1,1e-2,1e-3,1e-4,1e-5] 9 1

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
DM = str2num(arg_list{3});
cs = str2num(arg_list{4});
ts = str2num(arg_list{5});
ds = str2num(arg_list{6});
gam = str2num(arg_list{7});
trper=str2num(arg_list{8});
dvper=str2num(arg_list{9});

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

printf("Dimension;Kernel;C;Grado;Gamma;Error\n");

N=rows(Xdv);


for dim = DM
    # Se proyecta:
    XtrP = Xtr*W(:, 1:dim);
    XdvP = Xdv*W(:, 1:dim);
    # Se normaliza:
    XtrP = (XtrP'./max(XtrP'))';
    XdvP = (XdvP'./max(XdvP'))';

    for j=1:length(ts) # Para cada ts (kernels)
        for k=1:length(cs) # Para cada cs
            if ts(j) == 0 # En caso de que sea un kernel lineal
                # Entrenando
                res = svmtrain(xltr, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k))]);
                # Prediciendo
                [pred, accuracy, d] = svmpredict(xldv, XdvP, res, '-q');
                p = 1-(accuracy(1) / 100);
                printf("%d;%d;%d;-;-;%.3f\n",dim,ts(j),cs(k),p * 100);
            endif
            if ts(j) == 1 # En caso de que sea un kernel polinomial, se prueban los diferentes grados ds
                for i=1:length(ds) # Para cada ds (grado)
                    # Entrenando
                    res = svmtrain(xltr, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k)), " -d ", num2str(ds(i))]);
                    # Prediciendo
                    [pred, accuracy, d] = svmpredict(xldv, XdvP, res, '-q');
                    p = 1-(accuracy(1) / 100);
                    printf("%d;%d;%d;%d;-;%.3f\n",dim,ts(j),cs(k),ds(i),p * 100);
                end
            endif
            if ts(j) == 2 || ts(j) == 3
                for gm = gam
                    # Entrenando
                    res = svmtrain(xltr, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k))," -g ",num2str(gm)]);
                    # Prediciendo
                    [pred, accuracy, d] = svmpredict(xldv, XdvP, res, '-q');
                    p = 1- (accuracy(1) / 100);
                    printf("%d;%d;%d;-;%d;%.3f\n",dim,ts(j),cs(k),gm,p * 100);
                end
            endif
        end
    end
end

