import java.net.*;
import java.util.*;
import java.io.*;

class Servicio extends Thread {
    Socket cliente; //atributode la clasepublic 
    Servicio(Socket s) {// constructor de la clase
        cliente = s;// Código a ejecutar durante la inicialización
    }

    public void run() {
        // Código del hilo
        // Aquí ponemos lo que queremos que ejecute cada hilo
        // En nuestro caso el diálogo con el cliente
        try{
            Scanner entrada= new Scanner(cliente.getInputStream());
            PrintWriter salida= new PrintWriter(cliente.getOutputStream(),false);
            String flag = entrada.nextLine();
            while(!flag.equalsIgnoreCase("FIN")){
                salida.println(flag);
                salida.flush();
                flag = entrada.nextLine();
            }
            
            salida.close();
            entrada.close();
            cliente.close();
        }
        catch(IOException e){}
    }
}