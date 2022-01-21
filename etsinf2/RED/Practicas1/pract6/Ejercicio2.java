import java.net.*;
import java.io.*;
import java.util.*;

public class Ejercicio2
{
    public static void main(String argv[]) throws UnknownHostException, IOException {
        int puerto=7777;//puerto bien conocido del servidor
        ServerSocket servidor=new ServerSocket(puerto);
        while (true) {
            Socket cliente=servidor.accept();//Espero un cliente
            // Para atender la peticiónse crea un objeto Servicio
            // Se ejecuta el constructor sobre el socket “cliente”
            Servicio Cl=new Servicio(cliente);
            // Y se arranca el hilopara atender al cliente en paralelo 
            Cl.start();
        }//Fin While
    }// Fin Main
}//Fin ServidorConcurrente