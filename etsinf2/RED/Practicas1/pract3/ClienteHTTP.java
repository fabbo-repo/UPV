import java.util.*;
import java.io.*;
import java.net.*;

public class ClienteHTTP
{
    public static void main(String[] args){
        System.setProperty("line.separator","\r\n");
        try{
            Socket sc = new Socket("www.upv.es",80);
            Scanner lee = new Scanner(sc.getInputStream());
            PrintWriter pw = new PrintWriter(sc.getOutputStream(),false);
            pw.println("GET / HTTP/1.0");
            pw.println();
            pw.flush();
            while(lee.hasNextLine())
            System.out.println(lee.nextLine());
            pw.close();
            lee.close();
            sc.close();
            
        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
