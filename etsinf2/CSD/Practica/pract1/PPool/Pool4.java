// CSD feb 2013 Juansa Sendra

public class Pool4 extends Pool { //kids cannot enter if there are instructors waiting to exit
    protected int kidswimming;//niños nadando
    protected int inswimming;//instructores nadando
    protected int cap;//aforo
    protected int ki;//K/i
    protected int inswexit;//instructores esperando para salir

    public void init(int ki, int cap){
        this.kidswimming=0;
        this.inswimming=0;
        this.cap=cap;
        this.ki=ki;
        this.inswexit = 0;
    }

    public synchronized void kidSwims() throws InterruptedException{
        while(inswexit!=0||cap<=kidswimming+inswimming||ki*inswimming<=kidswimming){
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
        notifyAll();
        log.swimming();
        this.inswimming++;
    }

    public synchronized void instructorRests() throws InterruptedException{
        inswexit++;
        while(this.kidswimming!=0 && kidswimming>ki*(inswimming-1)){
            log.waitingToRest();wait();}
        inswexit--;
        log.resting();
        this.inswimming--;
    }
}
