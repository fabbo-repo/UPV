import java.util.*;
import java.net.*;

public class ExecFast
{
    public static void main(String[] args){
        try{
            Process cs = Runtime.getRuntime().exec("javac ChatServer.java");
            Process cc = Runtime.getRuntime().exec("javac ChatClientCSD.java");
            Process cui = Runtime.getRuntime().exec("javac ChatUI.java");
            InetAddress address = InetAddress.getLocalHost();
            System.out.println("IP local: " + address.getHostAddress());            
            //rmiregistry 9000
            Thread rmi = new Thread(new Runnable(){
                        public void run(){try{Process rmi = Runtime.getRuntime().exec("rmiregistry 9000");}catch(Exception e){}
                        }
                    });rmi.start();
            System.out.println("rmi en proceso");
            //java ChatServer nsport=9000 myport=9001
            Thread chatsev = new Thread(new Runnable(){
                        public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatServer nsport=9000 myport=9001");}catch(Exception e){}
                        }
                    });chatsev.start();
            System.out.println("ChatServer en proceso");
            Thread chatrob = new Thread(new Runnable(){
                        public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatRobot nsport=9000 myport=9002");}catch(Exception e){}
                        }
                    });chatrob.start();
            System.out.println("ChatRobot en proceso");
            //java ChatClient nshost=192.168.1.1 nsport=9000 myport=9002
            Thread chatClient = new Thread(new Runnable(){
                        public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatClientCSD nsport=9000 myport=9003");}catch(Exception e){}
                        }
                    });chatClient.start();

            System.out.println("ChatClient en proceso");

        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
