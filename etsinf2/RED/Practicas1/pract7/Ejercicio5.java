import java.net.*;
import java.util.*;

public class Ejercicio5
{
    public static void main(String[] args){
        try{
            DatagramSocket ds = new DatagramSocket(7777);
            byte[] buffer = new byte[512];
            DatagramPacket p = new DatagramPacket(buffer, 512);
            ds.receive(p);
            
            Date now = new Date();
            String now_string= now.toString() + "\r\n";
            p.setData( now_string.getBytes());
            p.setLength( now_string.length());
            ds.send(p);
            
            ds.close();
            
        }
        catch(Exception e){System.out.println(e.toString());}

    }
}
