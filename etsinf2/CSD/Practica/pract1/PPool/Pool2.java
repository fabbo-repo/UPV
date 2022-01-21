// CSD feb 2015 Juansa Sendra

public class Pool2 extends Pool{ //max kids/instructor
    protected int kidswimming;//niños
    protected int inswimming;//instructores
    protected int ki;//max kids/instructor

    public void init(int ki, int cap){
        this.kidswimming=0;
        this.inswimming=0;
        this.ki=ki;
    }

    public synchronized void kidSwims() throws InterruptedException{
        while(ki*inswimming<=kidswimming){
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
        while(this.kidswimming!=0 && kidswimming>ki*(inswimming-1)){
            log.waitingToRest();wait();}
        log.resting();
        this.inswimming--;
    }
}
