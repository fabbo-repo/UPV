// CSD feb 2015 Juansa Sendra

public class Pool3 extends Pool{ //max capacity
    protected int kidswimming;//niños
    protected int inswimming;//instructores
    protected int cap;
    protected int ki;

    public void init(int ki, int cap){
        this.kidswimming=0;
        this.inswimming=0;
        this.cap=cap;
        this.ki=ki;
    }

    public synchronized void kidSwims() throws InterruptedException{
        while(cap<=kidswimming+inswimming || ki*inswimming<=kidswimming){
            log.waitingToSwim();wait();}
        log.swimming();
        this.kidswimming++;
    }

    public synchronized void kidRests(){
        log.resting();
        this.kidswimming--;
        notifyAll();
    }

    public synchronized void instructorSwims() throws InterruptedException{
        while(cap<=kidswimming+inswimming){
            log.waitingToSwim();wait();}
        log.swimming();
        this.inswimming++;
    }

    public synchronized void instructorRests() throws InterruptedException{
        while(this.kidswimming!=0 && kidswimming>ki*(inswimming-1)){
            log.waitingToRest();wait();}
        log.resting();
        this.inswimming--;
        notifyAll();
    }
}
