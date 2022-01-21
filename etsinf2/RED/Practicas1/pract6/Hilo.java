
/**
 * Ejercicio 1
 */
public class Hilo extends Thread
{
    private String s;
    public Hilo(String s){
        this.s=s;
    }

    @Override
    public void run(){
        for(int i=0;i<10;i++){
            System.out.println(this.s);
            try{sleep(1000);}
            catch(InterruptedException e){}
        }
    }
}
