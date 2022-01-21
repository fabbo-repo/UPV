import java.net.*;
/**
 * Write a description of class Ejercicio1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Ejercicio1
{
    public static void main(String[] args){
        try{
            InetAddress ipServer = InetAddress.getByName(args[0]);
            System.out.println(ipServer.toString());
            
        }
        catch (Exception e){System.out.println(e.toString());}
    }
}
