import java.net.*;
import java.io.*;
import java.util.Scanner;

public class ClienteSMTP {

    static void error(String cadena) {
        System.out.println(cadena);
        System.exit(0);
    }

    public static void main(String args[]) {
        try{
            System.setProperty ("line.separator","\r\n");
            Socket s=new Socket("serveis-rdc.redes.upv.es", 25);
            System.out.println("Conectado al servidor SMTP de serveis-rdc");
            PrintWriter salida = new PrintWriter(s.getOutputStream());
            Scanner entrada=new Scanner(s.getInputStream());
            String respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("220")) 
            {error(respuesta);}

            salida.println("HELO [158.42.180.7]");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("250")) {error(respuesta);}

            salida.println("MAIL FROM:<redes07@redes.upv.es> BODY=8BITMIME SIZE=456");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("250")) {error(respuesta);}

            salida.println("RCPT TO:<redes09@redes.upv.es>");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("250")) {error(respuesta);}

            salida.println("DATA");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("354")) {error(respuesta);}

            // **completar** 
            // Aqui van varios println con todo el correo 
            // electronico incluidas las cabeceras
            salida.println("To: redes09@redes.upv.es");
            salida.println("From: Alumno de Redes <redes07@redes.upv.es>");
            salida.println("Subject: Test");
            salida.println("Message-ID: <fee36e6c-7883-ce8f-d103-b4436259bf39@redes.upv.es>");
            salida.println("Date: Wed, 16 Oct 2019 15:21:50 +0200");
            salida.println("User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Thunderbird/60.8.0");
            salida.println("MIME-Version: 1.0");
            salida.println("Content-Type: text/plain; charset=utf-8; format=flowed");
            salida.println("Content-Transfer-Encoding: 8bit");
            salida.println("");
            salida.println("Aqui está el cuerpo del mail.");
            salida.println("");
            salida.println(".");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("250")) {error(respuesta);}

            salida.println("QUIT");
            salida.flush();
            respuesta = entrada.nextLine();
            System.out.println(respuesta);
            if (!respuesta.startsWith("221")) {error(respuesta);}

            s.close();
            System.out.println("Desconectado");

        } catch (UnknownHostException e) {
            System.out.println("Host desconocido");
            System.out.println(e);
        } catch (IOException e) {
            System.out.println("No se puede conectar");
            System.out.println(e);
        }
    }
}
