import java.util.*;
import java.net.*;
import java.io.*;

public class cliente extends Thread 
{
    Socket servidor;

    public static void main(){
        try{
            Socket server = new Socket("rdc00.redes.upv.es",7777);
            cliente A = new cliente(server);
            A.start();

            Scanner kbd = new Scanner(System.in);
            PrintWriter salida = new PrintWriter(server.getOutputStream());
            String en = kbd.nextLine();
            while(!en.equals("quit")){
                salida.println(en);
                salida.flush();
                en = kbd.nextLine();
            }
            A.stop();
            salida.close();
            server.close();
            kbd.close();
        }
        catch(Exception e){}

    }

    cliente(Socket s) {// constructor de la clase
        this.servidor = s;// Código a ejecutar durante la inicialización
    }

    public void run() {
        // Código del hilo
        // Aquí ponemos lo que queremos que ejecute cada hilo
        // En nuestro caso el diálogo con el cliente
        try{
            Scanner entrada= new Scanner(this.servidor.getInputStream());
            String flag = entrada.nextLine();
            while(!flag.equals("")){
                System.out.println(flag);
                flag = entrada.nextLine();
            }
            entrada.close();

        }
        catch(IOException e){}
    }
}
