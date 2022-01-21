import java.net.*;

public class Ejercicio2
{
    public static void main(String[] args){
        for(int i = 0; i<5;i++){
            try{
                DatagramSocket ds = new DatagramSocket();
                int p = ds.getLocalPort();
                System.out.println("Puerto que otorga el sistema al cliente: "+p);
                ds.close();
            }
            catch(Exception e){System.out.println(e.toString());}
        }
    }
}
