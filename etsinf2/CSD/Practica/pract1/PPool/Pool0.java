// CSD feb 2015 Juansa Sendra

public class Pool0 extends Pool {	//free access
    public void init(int ki, int cap){}

    public synchronized void kidSwims(){log.swimming();}

    public synchronized void kidRests(){log.resting(); }

    public synchronized void instructorSwims(){log.swimming();}

    public synchronized void instructorRests(){log.resting(); }
}
