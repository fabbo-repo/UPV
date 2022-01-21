#!/usr/bin/octave -qf

if (nargin!=9)
printf("Usage: svm-eva.m <trdata> <trlabels> <tedata> <telabels> <D> <cs> <ts> <ds>\n")
exit(1);
end;

# ./pca+svm-eva.m mnist/trainX.mat.gz mnist/trainxl.mat.gz mnist/testY.mat.gz mnist/testyl.mat.gz 50 1 2 0 1e-1

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
tedata=arg_list{3};
telabs=arg_list{4};
DM = str2num(arg_list{5});
cs = str2num(arg_list{6});
ts = str2num(arg_list{7});
ds = str2num(arg_list{8});
gam = str2num(arg_list{9});

load(trdata);
load(trlabs);
load(tedata);
load(telabs);

N = rows(Y);

[m, W] = pca(X);
Xtr = X - m;
Ydv = Y - m;

printf("Dimension;Kernel;C;Grado;Gamma;Error;Intervalos\n");

for dim = DM
    # Se proyecta:
    XtrP = Xtr*W(:, 1:dim);
    YdvP = Ydv*W(:, 1:dim);
    # Se normaliza:
    XtrP = (XtrP'./max(XtrP'))';
    YdvP = (YdvP'./max(YdvP'))';

    for j=1:length(ts) # Para cada ts (kernels)
        for k=1:length(cs) # Para cada cs
            if ts(j) == 0 # En caso de que sea un kernel lineal
                # Entrenando
                res = svmtrain(xl, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k))]);
                # Prediciendo
                [pred, accuracy, d] = svmpredict(yl, YdvP, res, '-q');
                p = 1-(accuracy(1) / 100);
                intervalo = 1.96* sqrt((p * (1-p))/N);
                printf("%d;%d;%d;-;-;%.3f;[%.3f - %.3f]\n",dim,ts(j),cs(k),p * 100,(p-intervalo)*100,(p+intervalo)*100);
            endif
            if ts(j) == 1 # En caso de que sea un kernel polinomial, se prueban los diferentes grados ds
                for i=1:length(ds) # Para cada ds (grado)
                    # Entrenando
                    res = svmtrain(xl, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k)), " -d ", num2str(ds(i))]);
                    # Prediciendo
                    [pred, accuracy, d] = svmpredict(yl, YdvP, res, '-q');
                    p = 1-(accuracy(1) / 100);
                    intervalo = 1.96* sqrt((p * (1-p))/N);
                    printf("%d;%d;%d;%d;-;%.3f;[%.3f - %.3f]\n",dim,ts(j),cs(k),ds(i),p * 100,(p-intervalo)*100,(p+intervalo)*100);
                end
            endif
            if ts(j) == 2 || ts(j) == 3
                for gm = gam
                    # Entrenando
                    res = svmtrain(xl, XtrP, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k))," -g ",num2str(gm)]);
                    # Prediciendo
                    [pred, accuracy, d] = svmpredict(yl, YdvP, res, '-q');
                    p = 1- (accuracy(1) / 100);
                    intervalo = 1.96* sqrt((p * (1-p))/N);
                    printf("%d;%d;%d;-;%d;%.3f;[%.3f - %.3f]\n",dim,ts(j),cs(k),gm,p * 100,(p-intervalo)*100,(p+intervalo)*100);
                end
            endif
        end
    end
end

