package librerias.estructurasDeDatos.lineales;

public class LEGListaConPIOrdenada<E extends Comparable<E>> extends LEGListaConPI<E> 
{
    @Override 
    public void insertar(E e){
        this.inicio();
        while(!this.esFin() && e.compareTo(this.recuperar())>0){
            this.siguiente();
        }
        
        super.insertar(e);
    }
}
