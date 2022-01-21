import java.net.*;

public class Ejercicio3
{
    public static void main(String[] args){
        try{
            String ms = new String("Hola");
            DatagramPacket dp = new DatagramPacket(ms.getBytes(),
                    ms.getBytes().length, InetAddress.getByName("localhost"),7777);
            DatagramSocket ds = new DatagramSocket();
            ds.send(dp);
            ds.close();
        }
        catch(Exception e){System.out.println(e.toString());}

    }
}
