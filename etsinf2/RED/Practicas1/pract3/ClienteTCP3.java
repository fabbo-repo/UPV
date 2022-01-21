import java.io.*;
import java.net.*;

public class ClienteTCP3
{
    public static void main(String[] args){
        try{
            Socket s = new Socket("www.upv.es",81);
            //"www.upv.es",80
            System.out.println("¡Conectado!");
            s.close();
        }
        catch(NoRouteToHostException e){System.out.println("No es posible realizar conexión");}
        catch(UnknownHostException e){System.out.println("Nombre de servidor desconocido");}
        catch(IOException e){System.out.println("No es posible realizar conexión");}

    }
}

