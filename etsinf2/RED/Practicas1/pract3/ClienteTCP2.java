import java.net.*;
import java.io.*;

public class ClienteTCP2{
    public static void main(String[] args) throws IOException, UnknownHostException {
        Socket s = new Socket("www.upv.es",81);
        //"www.upv.es",80
        System.out.println("¡Conectado!");
        s.close();

    }

}
