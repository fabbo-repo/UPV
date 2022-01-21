
/**
 * class Figure.
 * 
 * @author LTP 
 * @version 2018-19
 */

public abstract class Figure implements Comparable {
    protected double x;
    protected double y;

    public Figure(double x, double y) {
        this.x = x; 
        this.y = y; 
    }

    public boolean equals(Object o) {
        if (!(o instanceof Figure)) { return false; }
        Figure f = (Figure) o;
        return x == f.x && y == f.y;
    }

    public String toString() {
        return "Position: (" + x + ", " + y + ")"; 
    }

    protected abstract double area();

    public int compareTo(Object o){
        if(o instanceof Figure){
            if(this.area()==((Figure)o).area())return 0;
            else if(this.area()<((Figure)o).area())return -1;
            else return 1; 
        }
        else{throw new ClassCastException();}
    }
}