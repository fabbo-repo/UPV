package theantsproblem.Ejercicio4;

import java.util.concurrent.locks.*;
/**
 * Made by Fabbo
 */
public class TerritoryLock {
    private int tam; // Matrix size
    Lock lockgeneral;
    Lock lock[][];//Para solución tryLock
    String description = "tryLock/isLocked example";
    private Log log;

    public String getDesc() {
        return description;
    }

    public TerritoryLock(int tamT, Log l) {
        tam = tamT;
        lockgeneral = new ReentrantLock();
        log = l;
        lock = new Lock[tam][tam];
        // Initializing the matrix
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                lock[i][j] = new ReentrantLock(); //Para solución tryLock
            }
        }
    }

    public int getTam() {
        return tam;
    }

    public synchronized void putAnt(Ant h, int x, int y) {
        if(lock[x][y].tryLock()) {
            h.setPosition(x, y);
            // Write in the log: ant inside territory
            log.writeLog(LogItem.PUT, h.getid(), x, y, LogItem.OK, "Ant " + h.getid() + " : [" + x + "," + y + "]  inside");

        }
        else{
            if(x<tam-1)putAnt(h, x+1,y);
            else if(y<tam-1)putAnt(h, x,y+1);
            else putAnt(h, x-1,y);
        }

    }

    public synchronized void takeAnt(Ant h) {
        int x = h.getX();
        int y = h.getY();

        // Write in the log: ant outside territory
        log.writeLog(LogItem.TAKE, h.getid(), x, y, LogItem.OUT, "Ant " + h.getid() + " : [" + x + "," + y + "] out");
        lock[x][y].unlock();

    }

    public synchronized void moves(Ant h, int x1, int y1, int step) {
        int x = h.getX();
        int y = h.getY();
        boolean flag = false;
        if(lock[x1][y1].tryLock()) {
            flag = true;
            h.setX(x1);
            h.setY(y1);
            // Write in the log: ant moving
            log.writeLog(LogItem.MOVE, h.getid(), x1, y1, LogItem.OK,
                "Ant " + h.getid() + " : [" + x + "," + y + "] -> [" + x1 + "," + y1 + "] step:" + step);

        }
        else{}
        
        if(flag) lock[x][y].unlock();
    }
}
