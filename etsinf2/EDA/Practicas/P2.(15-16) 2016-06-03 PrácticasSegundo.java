public int masLejosDe(int v){
    int masAlejado = -1;
    visitados = new int[numVertices()];
    visitados[v]=1;
    
    MonticuloBinarioR0<Arista> caminosMin = new MonticuloBinarioR0<>();
    ListaConPI<Adyacente> l = adyacentesDe(v);
    
    for(l.inicio(); !l.esFin(); l.siguiente()){
        caminosMin.insertar(new Arista(v,l.recuperar().getDestino(),l.recuperar().getPeso()));
    }
    
    while(!caminosMin.esVacia()){
        int vertice = caminosMin.eliminarMin().getDestino();
        if(visitados[vertice]==0){
            l = adyacentesDe(vertice);
            visitados[vertice] = 1;

            for(l.inicio(); !l.esFin(); l.siguiente()){
                caminosMin.insertar(new Arista(vertice,l.recuperar().getDestino(),l.recuperar().getPeso()));
            }
            
            masAlejado = vertice;
        }
    }

    return masAlejado;
}