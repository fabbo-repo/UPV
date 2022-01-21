
/**
 * class Triangle.
 * 
 * @author LTP
 * @version 2018-19
 */

public class Triangle extends Figure {
    private double base; 
    private double height;

    public Triangle(double x, double y, double b, double h) {
        super(x, y);
        base = b;
        height = h;
    }

    public String toString() {
        return "Triangle:\n\t" +
            super.toString() +
            "\n\tBase: " + base +
            "\n\tHeight: " + height;
    }
    
    public boolean equals(Object o){
        return super.equals(o) 
        && o instanceof Triangle 
        && ((Triangle)o).base == base
        && ((Triangle)o).height == height;
    }

    public double area(){return base * height / 2;}
}