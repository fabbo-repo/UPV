package theantsproblem;


public class MyExam extends Thread
{
    private int i;
    private String name;
    
    public MyExam(int num)
    {
        i= num;
        name="Task "+num;
    }
    
    public void run(){
        currentThread().setName(name);
        for(int j = 0; j < i; j++){
            if((j%2)==0){new MyExam(j).start();}
            else{Thread.yield();}
        }
        System.out.println("Thread: "+currentThread().getName());
    }

    public static void xd(){
        MyExam ex = new MyExam(6);
        ex.start();
        try{
            ex.join();
        }
        catch(InterruptedException e){System.out.println("Bye bye");}
    }
}
