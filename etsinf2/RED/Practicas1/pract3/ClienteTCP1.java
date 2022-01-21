import java.net.*;
import java.io.*;

public class ClienteTCP1
{
    public static void main(String[] args) throws IOException, UnknownHostException {
        //InetAddress dirIP = InetAddress.getByName(“www.upv.es”)
        Socket s = new Socket("www.upv.es",80);
        //"www.upv.es",80
        System.out.println("¡Conectado!");
        s.close();
    }
}
