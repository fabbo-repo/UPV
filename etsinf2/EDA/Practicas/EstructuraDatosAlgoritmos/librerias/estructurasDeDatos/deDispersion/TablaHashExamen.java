package librerias.estructurasDeDatos.deDispersion;

import librerias.estructurasDeDatos.modelos.ListaConPI; 
import librerias.estructurasDeDatos.lineales.LEGListaConPI;
//import librerias.estructurasDeDatos.deDispersion.EntradaHash;

/**
 * TablaHashExamen: version CORRECTA y SIMPLIFICADA    
 * de la clase TablaHash (SIN Rehashing, SIN claves(),  
 * SIN recuperar(e), sin eliminar(e), etc.). Como    
 * en Tabla Hash, las cubetas, o listas de colisiones,   
 * se representan mediante Listas con PI de EntradaHash<C, V>
 *
 * @author EDA-QB
 * @version PRIMER PARCIAL 2019-20
 */

public class TablaHashExamen<C, V> {

    public static final double FACTOR_CARGA = 0.75;
    protected ListaConPI<EntradaHash<C, V>>[] elArray;
    protected int talla;

    /** Metodo cuyo cuerpo se debe completar en esta prueba
     *  
     * Dada una Clave c, devuelve con coste minimo un String tal que:
     * (a) Contiene los valores de las claves de la Tabla que colisionan
     *      con c, separados entre si por un espacio en blanco.
     * (b) Su ultimo elemento es el numero de colisiones que se han 
     *     producido para obtener los valores de las claves de la Tabla
     *     que colisionan con c, precedido por el literal "con coste "
     *
     * IMPORTANTE: el String resultado NO debe contener el valor asociado 
     * a la clave c, por lo que si c NO colisiona con ninguna clave de la 
     * Tabla el metodo debe devolver el String "con coste 0"
     */
    public String colisionanCon(C c) {
        int id = this.indiceHash(c);

        if(elArray[id].talla()==0){return "con coste 0";}
        else{
            ListaConPI<EntradaHash<C, V>> aux = elArray[id];
            int i = 0;String res = "";
            for(aux.inicio(); !aux.esFin(); aux.siguiente()){
                res+= aux.recuperar().clave + " ";
                i++;
            }
            res+="con coste "+i;
            return res;
        }
        /*COMPLETAR*/
    }

    /***************NO PUEDES MODIFICAR EL CODIGO QUE SIGUE**************/

    @SuppressWarnings("unchecked") 
    public TablaHashExamen(int tallaMaximaEstimada) {
        int capacidad = (int) (tallaMaximaEstimada / FACTOR_CARGA);
        capacidad = siguientePrimo(capacidad);
        elArray = new LEGListaConPI[capacidad];
        for (int i = 0; i < elArray.length; i++) {
            elArray[i] = new LEGListaConPI<EntradaHash<C, V>>();
        }
        talla = 0;
    }

    protected static final int siguientePrimo(int n) {
        int aux = n;
        if (aux % 2 == 0) { aux++; }
        for ( ; !esPrimo(aux); aux += 2) { ; }
        return aux;
    } 

    protected static final boolean esPrimo(int n) {
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) { return false; }
        }
        return true;
    }

    public static int nH = 0;
    protected int indiceHash(C c) {
        nH++;
        int indiceHash = c.hashCode() % this.elArray.length;
        if (indiceHash < 0) { indiceHash += this.elArray.length; }
        return indiceHash;
    }

    public V insertar(C c, V v) {
        int pos = indiceHash(c);
        ListaConPI<EntradaHash<C, V>> l = elArray[indiceHash(c)];
        V antiguoValor = null;
        l.inicio();
        while (!l.esFin() && !l.recuperar().clave.equals(c)) { 
            l.siguiente(); 
        }
        if (l.esFin()) {
            l.insertar(new EntradaHash<C, V>(c, v));
            talla++;
        }
        else {
            antiguoValor = l.recuperar().valor; l.recuperar().valor = v;
        }
        return antiguoValor;
    }
}