
/**
 * class WrapperClassesUse.
 * 
 * @author LTP 
 * @version 2018-19
 */

public class WrapperClassesUse {        
    public static void main(String[] args) {            
        // Assignment of wrapper variables to elementary types 
        int i = new Integer(1234567);		
        long l = new Long(1234567890);		
        short sh = new Short((short) i);
        byte b = new Byte((byte) i);
        float f = new Float(123456.65f);
        double d = new Double(1234567.7654321);
        char c = new Character('c');
        boolean bl = new Boolean(true);

        // Writing elementary variables
        System.out.println("int i = " + i);
        System.out.println("long l = " + l);
        System.out.println("short sh = " + sh);
        System.out.println("byte b = " + b);
        System.out.println("float f = " + f);
        System.out.println("double d = " + d);
        System.out.println("char c = " + c);
        System.out.println("boolean bl = " + bl);

        // Assignment of elementary values to wrapper variables
        Integer eI = 123456; 
        Long eL =(long) 1234567890;
        Short eS = (short) 1234567;
        Byte eBy = (byte) 1234567;
        Float eF = 123456.65f;
        Double eD = 1234567.7654321;
        Character eC = 'c';
        Boolean eB = true;

        // Writing wrapper variables
        System.out.println("\nInteger I = " + eI);
        System.out.println("Long L = " + eL);
        System.out.println("Short Sh = " + eS);
        System.out.println("Byte B = " + eBy);
        System.out.println("Float F = " + eF);
        System.out.println("Double D = " + eD);
        System.out.println("Character C = " + eC);
        System.out.println("Boolean BL = " + eB);

    }    
}