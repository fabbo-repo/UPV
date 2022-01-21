import java.util.*;

/**
 * @author Fabianno
 */
public class Exec{
    public static void main(String[] args){
        try{
            Scanner cmd = new Scanner(System.in);
            Process cs = Runtime.getRuntime().exec("javac ChatServer.java");
            Process cc = Runtime.getRuntime().exec("javac ChatClientCSD.java");
            Process cui = Runtime.getRuntime().exec("javac ChatUI.java");

            //rmiregistry 9000
            System.out.println("¿Deseas ejecutar rmiregistry? (Si/No)");
            String answer = cmd.nextLine().toLowerCase();
            if(answer.equals("si")){
                Thread rmi = new Thread(new Runnable(){
                            public void run(){try{Process rmi = Runtime.getRuntime().exec("rmiregistry 9000");}catch(Exception e){}
                            }
                        });rmi.start();
                System.out.println("rmi en proceso");
            }
            //java ChatServer nsport=9000 myport=9001
            System.out.println("\n¿Deseas ejecutar ChatServer? (Si/No)");
            answer = cmd.nextLine().toLowerCase();
            if(answer.equals("si")){
                Thread chatsev = new Thread(new Runnable(){
                            public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatServer nsport=9000 myport=9001");}catch(Exception e){}
                            }
                        });chatsev.start();
                System.out.println("ChatServer en proceso");
            }
            //java ChatClient nshost=192.168.1.1 nsport=9000 myport=9002
            System.out.println("\nProcediendo a crear ChatClient(s)");
            System.out.println("¿Cuántos creo?");
            int n = Integer.parseInt(cmd.nextLine()); 
            System.out.println("¿Con dir IP de otro pc? (Si/No)");
            answer = cmd.nextLine().toLowerCase();
            final String nhost;
            if(answer.equals("si")){System.out.print("nHost: ");nhost = cmd.nextLine().toLowerCase();System.out.println();}else{nhost="";}
            System.out.print("nsPort: "); final int nsport = Integer.parseInt(cmd.nextLine());System.out.println(); 
            for(int i = 0; i < n; i++){
                System.out.println("ChatClient "+(i+1));System.out.print("myPort: ");final int myport = Integer.parseInt(cmd.nextLine());System.out.println();
                if(nhost.length()!=0){
                    Thread chatClient = new Thread(new Runnable(){
                                public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatClientCSD nshost="+nhost+"nsport="+nsport+" myport="+myport);}catch(Exception e){}
                                }
                            });chatClient.start();
                }
                else{
                    Thread chatClient = new Thread(new Runnable(){
                                public void run(){try{Process chatsev = Runtime.getRuntime().exec("java ChatClientCSD nsport="+nsport+" myport="+myport);}catch(Exception e){}
                                }
                            });chatClient.start();
                }

            }
            System.out.println(n+" ChatClient en proceso");

        }
        catch(Exception e){System.out.println(e.toString());}
    }
}
