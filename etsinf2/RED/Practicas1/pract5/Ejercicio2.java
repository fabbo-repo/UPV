import java.util.*;
import java.io.*;
import java.net.*;

public class Ejercicio2
{
    public static void main(String[] args){
        try{
            ServerSocket ss = new ServerSocket(7777);
            while(true){
                Socket s = ss.accept();
                System.out.println("S Local Adress: "+s.getLocalAddress() +"\n");
                System.out.println("S Local Port: "+s.getLocalPort() +"\n");
                System.out.println("S Inet Adress: "+s.getInetAddress()+"\n");
                System.out.println("S Port: "+s.getPort()+"\n");
                System.out.println("SS Inet Adress: "+ss.getInetAddress()+"\n");
                System.out.println("SS Local Port: "+ss.getLocalPort()+"\n");

                s.close();
            }
        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
