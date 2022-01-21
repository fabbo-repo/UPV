# V es la matriz mxN de los índices de los m-NN de cada prototipo en X por columnas
# X es una matriz NxD de N prototipos
# xl es un vector de Nx1 etiquetas
# m es el número de vecinos más cercanos que almacenamos de cada prototipo
function [V]=mnn(X,xl,m)

    N=rows(X);

    # La matriz de distancias resultante ocupa N*N*4 bytes/1GB
    # por 4 para que ocupe 250 MB
    numbatches=ceil(N*N*4/1024^3)*4;
    if (numbatches<1) numbatches=1; end

    # Número de muestras en un batch para que este programa 
    # ocupe como máximo 250 MB de memoria
    batchsize=ceil(N/numbatches);

    V = [];

    for i=1:numbatches

    # Identificar las muestras (p.e. X(1,batchsize)) de cada batch de X, 
    # con tamaño batchsize
    Xbatch=X((i-1)*batchsize+1:min(i*batchsize,N),:);

    # D es una matriz N*batchsize de distancias donde los N-NN de cada prototipo
    # van por columnas. Tras ordenar la matriz, la primera fila sería cero, 
    # ya que la distancia de un prototipo con sí mismo es cero.
    D = L2dist(X,Xbatch);

    # Ordenando ascendentemente por columnas, de más cercana a más lejana
    [D,idx] = sort(D,'ascend');

    # Índices en X de los m vecinos más cercanos de cada prototipo en Xbatch
    # sin considerar al propio prototipo en Xbatch, 
    # suponiendo que no hay dos muestras iguales.
    idx = idx(2:m+1,:);

    V = [V idx];
    
    end
end
