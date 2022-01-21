// CSD feb 2015 Juansa Sendra

public class Pool1 extends Pool {
    protected int kidswimming;//niños
    protected int inswimming;//instructores

    public void init(int ki, int cap){
        this.kidswimming=0;
        this.inswimming=0;
    }

    public synchronized void kidSwims() throws InterruptedException{
        while(this.inswimming==0){
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
        log.swimming();
        this.inswimming++;
        notifyAll();
    }

    public synchronized void instructorRests() throws InterruptedException{
        while(this.kidswimming!=0 && inswimming==1){
            log.waitingToRest();wait();}
        log.resting();
        this.inswimming--;
    }
}
