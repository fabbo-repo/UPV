#!/usr/bin/octave -qf

if (nargin!=7)
    printf("Usage: svm-exp.m <trdata> <trlabels> <cs> <ts> <ds> <gam> <%%trper> <%%dvper>\n%d\n",nargin)
    exit(1);
end;

# ./svm-exp.m mnist/trainX.mat.gz mnist/trainxl.mat.gz [1,10,100,1000,10000] [0,1,2,3] [1,2,3,4,5] 9 1

arg_list=argv();
trdata=arg_list{1};
trlabs=arg_list{2};
cs = str2num(arg_list{3}); 
ts = str2num(arg_list{4});
ds = str2num(arg_list{5});
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

printf("Kernel;C;Grado;Error\n");

N=rows(Xdv);


for k=1:length(cs) # Para cada cs
    for j=1:length(ts) # Para cada ts (kernels)
        if ts(j) == 1 # En caso de que sea un kernel polinomial, se prueban los diferentes grados ds
            for i=1:length(ds) # Para cada ds
                # Entrenando
                res = svmtrain(xltr, Xtr, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k)), " -d ", num2str(ds(i))]);
                # Prediciendo
                [pred, accuracy, d] = svmpredict(xldv, Xdv, res, '-q');
                p = 1-(accuracy(1) / 100);
	            intervalo = 1.96* sqrt((p * (1-p))/N);
                printf("%d;%d;%d;%.3f\n",ts(j),cs(k),ds(i),p * 100);
            end
        else
            # Entrenando
            res = svmtrain(xltr, Xtr, ["-q -t ", num2str(ts(j)), " -c ", num2str(cs(k))]);
            # Prediciendo
            [pred, accuracy, d] = svmpredict(xldv, Xdv, res, '-q');
            p = 1- (accuracy(1) / 100);
	        intervalo = 1.96* sqrt((p * (1-p))/N);
            printf("%d;%d;-;%.3f\n",ts(j),cs(k),p * 100);
        endif
        # Cambo de kernel
    end
end