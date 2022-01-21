/**
 * class Rectangle.
 * 
 * @author Fabianno
 * @version 2018-19
 */

public class Rectangle extends Figure implements ComparableRange,Printable{
    protected double base; 
    protected double height;

    public Rectangle(double x, double y, double b, double h) {
        super(x, y);
        base = b;
        height = h;
    }

    @Override
    public String toString() {
        return "Rectangle:\n\t" +
        super.toString() +
        "\n\tBase: " + base +
        "\n\tHeight: " + height;
    }

    public boolean equals(Object o){
        return super.equals(o) 
        && o instanceof Rectangle 
        && ((Rectangle)o).base == base
        && ((Rectangle)o).height == height;
    }

    public double area(){return base * height;}

    @Override
    public int compareToRange(Object o){
        if(o instanceof Rectangle){
            Rectangle rec = (Rectangle) o;
            double aredif = Math.abs(this.area()-rec.area());
            double aresum = this.area()+rec.area();
            if(aredif<=0.1*aresum)return 0;
            return super.compareTo(o);
        }
        else throw new ClassCastException();
    }

    /** Figura 3. código para dibujar rectángulos */
    @Override
    public void print(char c){
        int b = (int) base;
        int h = (int) height;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < b; j++) {
                System.out.print(c);
            }
            System.out.println();
        } 
    }
}