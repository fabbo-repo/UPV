// CSD Mar 2013 Juansa Sendra

public class LimitedTable extends RegularTable { //max 4 in dinning-room
    protected int hilo_entered;
    
    public LimitedTable(StateManager state) {
        super(state);
        hilo_entered = 0;
    }
    
    @Override
    public synchronized void enter(int id) throws InterruptedException {
        while(hilo_entered>=4){state.wenter(id); wait();}
        hilo_entered++;state.enter(id);
    }
    
    @Override
    public synchronized void exit(int id){
        hilo_entered--;state.exit(id);notifyAll();
    }
}
