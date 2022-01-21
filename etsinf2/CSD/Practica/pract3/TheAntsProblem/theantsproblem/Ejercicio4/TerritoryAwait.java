package theantsproblem.Ejercicio4;

import java.util.concurrent.locks.*;
import java.util.concurrent.*;

/**
 * Made by Fabbo
 */
public class TerritoryAwait {
    private int tam; // Matrix size
    Lock lock;
    private boolean occupied[][];
    private Condition conditions[][];
    String description = "Await with TimeOut Example";
    private Log log;

    public String getDesc() {
        return description;
    }

    public TerritoryAwait(int tamT, Log l) {
        tam = tamT;
        occupied = new boolean[tam][tam];
        lock = new ReentrantLock();
        conditions = new Condition[tam][tam];
        log = l;
        // Initializing the matrix
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                occupied[i][j] = false;
                conditions[i][j] = lock.newCondition();
            }
        }
    }

    public int getTam() {
        return tam;
    }

    public void putAnt(Ant h, int x, int y) {
        lock.lock();
        boolean timeo = false;
        try{
            if(occupied[x][y]) {
                try {
                    // Write in the log: ant waiting
                    log.writeLog(LogItem.PUT, h.getid(), x, y, LogItem.WAITINS,
                        "Ant " + h.getid() + " waiting for [" + x + "," + y + "]");
                    conditions[x][y].await(1,TimeUnit.SECONDS);
                } 
                catch (InterruptedException e) {}
            }
            if(!occupied[x][y]){
                occupied[x][y] = true;
                h.setPosition(x, y);
                // Write in the log: ant inside territory
                log.writeLog(LogItem.PUT, h.getid(), x, y, LogItem.OK, "Ant " + h.getid() + " : [" + x + "," + y + "]  inside");
            }
        }
        finally{lock.unlock();}
    }

    public void takeAnt(Ant h) {
        lock.lock();
        try{
            int x = h.getX();
            int y = h.getY();
            occupied[x][y] = false;
            // Write in the log: ant outside territory
            log.writeLog(LogItem.TAKE, h.getid(), x, y, LogItem.OUT, "Ant " + h.getid() + " : [" + x + "," + y + "] out");
            conditions[x][y].signal();
        }
        finally{lock.unlock();}
    }

    public void moves(Ant h, int x1, int y1, int step) {
        lock.lock();
        try{
            int x = h.getX();
            int y = h.getY();

            if(occupied[x1][y1]) {
                try {
                    // Write in the log: ant waiting
                    log.writeLog(LogItem.MOVE, h.getid(), x1, y1, LogItem.WAIT,
                        "Ant " + h.getid() + " waiting for [" + x1 + "," + y1 + "]");
                    conditions[x1][y1].await(1,TimeUnit.SECONDS);
                } catch (InterruptedException e) {}
            }
            if(!occupied[x1][y1]){
                occupied[x][y] = false;
                occupied[x1][y1] = true;
                h.setX(x1);
                h.setY(y1);
                // Write in the log: ant moving
                log.writeLog(LogItem.MOVE, h.getid(), x1, y1, LogItem.OK,
                    "Ant " + h.getid() + " : [" + x + "," + y + "] -> [" + x1 + "," + y1 + "] step:" + step);
                conditions[x][y].signal();
            }
        }
        finally{lock.unlock();}
    }
}
