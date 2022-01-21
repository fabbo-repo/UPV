package lineales.librerias.aplicaciones;

import lineales.librerias.implementaciones.*;
import lineales.librerias.modelos.*;

public class QueueApp {
    public static void main(String[] args) { 
        for(int j = 0; j < 2;j++){
            QueueAC<Integer> c = new QueueAC<Integer>();
            QueueAL<Integer> v = new QueueAL<Integer>();;
            if(j==0){System.out.println("For QueueAC:");}
            else{System.out.println("\nFor QueueAL:");}

            for (int i = 1; i <= 15; i++) {
                if(j==0) c.enqueue(i);  
                else v.enqueue(i);  
            }
            if(j==0)System.out.println("Initial queue:\n" + c);
            else System.out.println("Initial queue:\n" + v);

            int toRemove = 10;
            for (int i = 0; i < toRemove; i++) {
                if(j==0) c.dequeue();
                else v.dequeue();
            }
            if(j==0)System.out.println("Queue after dequeing " 
                    + toRemove + " items:\n" + c);
            else System.out.println("Queue after dequeing " 
                    + toRemove + " items:\n" + v);

            int toInsert = 25;
            for (int i = 1; i <= toInsert; i++) {
                if(j==0) c.enqueue(i);
                else v.enqueue(i);
            }
            if(j==0)System.out.println("Queue after queing "
                    + toInsert + " items:\n" + c);   
            else System.out.println("Queue after queing "
                    + toInsert + " items:\n" + v);  
        }
    }
}