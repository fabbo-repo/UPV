import java.net.*;

public class Ejercicio4
{
    public static void main(String[] args){
        try{
            String ms = new String("hola xD\n");
            DatagramPacket dp = new DatagramPacket(ms.getBytes(),
                    ms.getBytes().length, InetAddress.getByName("localhost"),7777);
            DatagramSocket ds = new DatagramSocket();
            ds.send(dp);
            byte[] buffer = new byte[512];
            DatagramPacket p = new DatagramPacket(buffer, 512);
            ds.receive(p);
            ds.close();
            System.out.println(new String(p.getData(), 0, p.getLength()));
        }
        catch(Exception e){System.out.println(e.toString());}

    }
}
