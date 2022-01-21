import java.util.LinkedList;
import java.util.List;

/**
 * class FiguresGroup.
 * 
 * @author LTP 
 * @version 2018-19
 */

public class FiguresGroup implements Printable{
    private static final int NUM_FIGURES = 10;
    private Figure[] figuresList = new Figure[NUM_FIGURES];
    private int numF = 0;

    public void add(Figure f) { figuresList[numF++] = f; }

    public String toString() {
        String s = "";
        for (int i = 0; i < numF; i++) {
            s += "\n" + figuresList[i];
        }
        return s;
    }

    private boolean found(Figure f) {
        for (int i = 0; i < numF; i++) {
            if (figuresList[i].equals(f)) return true;
        }
        return false;
    }

    private boolean included(FiguresGroup g) {
        for (int i = 0; i < g.numF; i++) {
            if (!found(g.figuresList[i])) return false;
        }
        return true;
    }

    public boolean equals(Object o){
        return o instanceof FiguresGroup
        && this.included((FiguresGroup) o)
        && ((FiguresGroup) o).included(this);
    }

    public double area(){
        double suma = 0;
        for (int i = 0; i < numF; i++) {
            suma += figuresList[i].area();
        }
        return suma;
    }

    public Figure greatestFigure(){
        Figure mayor=null;
        if(numF>0){
            double mayora = figuresList[0].area();
            mayor=figuresList[0];
            for (int i = 1; i < numF; i++) {
                if(mayora<figuresList[i].area()){
                    mayor=figuresList[i];
                    mayora=figuresList[i].area();
                }
            }
        }
        return mayor;
    }

    public List orderedList(){
        List res = new LinkedList();
        if (numF > 0)
            for(int i = 1;i<numF;i++){
                int j = res.size() - 1;

                while(j>=0 && figuresList[i].compareTo(res.get(j))<0){j--;}
                res.add(j+1,figuresList[i]);

            }
        return res;
    }

    @Override
    public void print(char c) {
        for (int i = 0; i < numF; i++) {
            if(figuresList[i] instanceof Rectangle){
                Rectangle rec = (Rectangle) figuresList[i];
                rec.print(c);
            }
            else if(figuresList[i] instanceof Circle){
                Circle cir = (Circle) figuresList[i];
                cir.print(c);
            }
        }
    }
}