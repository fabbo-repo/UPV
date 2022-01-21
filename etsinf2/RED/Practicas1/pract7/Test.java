import java.net.*;

public class Test
{
    public static void main(String[] args){
        try{
            DatagramPacket dp = new DatagramPacket(new byte[512],512);
            DatagramSocket ds = new DatagramSocket(7777);
            ds.receive(dp);
            String s = new String(dp.getData(), 0, dp.getLength());
            System.out.println(s);
            ds.close();
            
        }
        catch(Exception e){System.out.println(e.toString());}

    }
}
