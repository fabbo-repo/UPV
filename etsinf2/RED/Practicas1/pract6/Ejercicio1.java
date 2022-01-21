
/**
 * Ejercicio 1
 */
public class Ejercicio1
{
    public static void main(){
        Hilo h1 = new Hilo("Hola soy 1");
        Hilo h2 = new Hilo("Hola soy 2");
        Hilo h3 = new Hilo("Hola soy 3");
        h1.start();h2.start();h3.start();
    }
}
