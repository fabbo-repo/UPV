import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ClienteDayTime
{
    public static void main(String[] args){
        try{
            Socket s = new Socket("zoltar.redes.upv.es",13);
            System.out.println("¡Conectado!");
            Scanner lee = new Scanner(s.getInputStream());
            System.out.println("Mensaje: \n"+lee.nextLine());
            s.close();
        }
        catch(NoRouteToHostException e){System.out.println("No es posible realizar conexión");}
        catch(UnknownHostException e){System.out.println("Nombre de servidor desconocido");}
        catch(IOException e){System.out.println("No es posible realizar conexión");}

    }
}
