import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ClienteEco
{
    public static void main(String[] args){
        try{
            Socket s = new Socket("zoltar.redes.upv.es",7);
            System.out.println("¡Conectado!");
            PrintWriter pw = new PrintWriter(s.getOutputStream(),false);
            //Autoflush a false (Solo funciona a la llamada de println)
            Scanner lee = new Scanner(s.getInputStream());
            pw.println("HolaMundo");
            pw.flush();
            System.out.println("Mensaje: \n"+lee.nextLine());
            pw.close();
            lee.close();
            s.close();
        }
        catch(NoRouteToHostException e){System.out.println("No es posible realizar conexión");}
        catch(UnknownHostException e){System.out.println("Nombre de servidor desconocido");}
        catch(IOException e){System.out.println("No es posible realizar conexión");}

    }
}
