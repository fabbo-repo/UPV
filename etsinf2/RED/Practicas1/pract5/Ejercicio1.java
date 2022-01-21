import java.util.*;
import java.io.*;
import java.net.*;

public class Ejercicio1
{
    public static void main(String[] args){
        try{
            ServerSocket ss = new ServerSocket(7777);
            while(true){
                Socket cliente = ss.accept();
                Scanner sc = new Scanner(cliente.getInputStream());
                String entrada = sc.nextLine();
                PrintWriter pw = new PrintWriter(cliente.getOutputStream(),false);
                pw.println(entrada);
                pw.flush();
                System.out.println("Se ha conectado un cliente al servidor.");
                sc.close();
                pw.close();
                cliente.close();
            }
        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
