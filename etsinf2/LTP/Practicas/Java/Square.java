/**
 * class Square.
 * 
 * @author Fabianno
 * @version 2018-19
 */

public class Square extends Rectangle {
    public Square(double x, double y, double l) {
        super(x, y, l, l);
    }

    public String toString() {
        return "Square:\n\t" +
        "Position: (" + x + ", " + y + ")"+
        "\n\tBase: " + base +
        "\n\tHeight: " + height;
    }

    public boolean equals(Object o){
        return super.equals(o) 
        && o instanceof Square;
    }
}