import java.util.*;
import java.io.*;
import java.net.*;

public class Ejercicio3
{
    public static void main(String[] args){
        try{
            ServerSocket ss = new ServerSocket(8000);
            while(true){
                Socket cliente = ss.accept();

                Scanner sc = new Scanner(cliente.getInputStream());

                PrintWriter pw = new PrintWriter(cliente.getOutputStream(),false);
                pw.print("HTTP/1.0 200 OK \r\n");
                pw.print("Content-Type: text/plain \r\n");
                pw.print("\r\n");
                pw.flush();
                System.out.println("Se ha conectado un cliente al servidor.");
                String entrada = sc.nextLine();
                while(!entrada.equals("")){
                    pw.println(entrada);
                    pw.flush();
                    entrada = sc.nextLine();
                }

                sc.close();
                pw.close();
                cliente.close();
            }
        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
