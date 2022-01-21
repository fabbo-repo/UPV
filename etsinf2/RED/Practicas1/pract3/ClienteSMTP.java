import java.util.*;
import java.io.*;
import java.net.*;

public class ClienteSMTP
{
    public void main(String[] args){
        System.setProperty("line.separator","\r\n");
        try{
            Socket sc = new Socket("smt.upv.es",25);
            Scanner lee = new Scanner(sc.getInputStream());
            System.out.println(lee.nextLine());
            PrintWriter pw = new PrintWriter(sc.getOutputStream(),false);
            pw.println("HELO rdc07.redes.upv.es");
            pw.flush();
            System.out.println(lee.nextLine());
            pw.close();
            lee.close();
            sc.close();
            
        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
