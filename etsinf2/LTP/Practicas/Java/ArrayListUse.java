import java.util.*;
import java.io.*;
import java.util.*;

/**
 * class ArrayListUse.
 * 
 * @author LTP
 * @version 2018-19
 */

public class ArrayListUse {       
    /*Te recomiendo que pongas {"array.txt"}*/
    public static void main(String[] args) {        
        if (args.length != 1) {
            System.err.print("You must specify an argument: filename");
            System.exit(0);
        }

        // Creating File object, Scanner object, ArrayList object
        File fd = new File(args[0]);
        Scanner file = null;
        ArrayList<String> list= new ArrayList<String>();
        try {
            file = new Scanner(fd);
        } 
        catch (FileNotFoundException e) {
            System.err.println("File does not exists " + e.getMessage());
            System.exit(0);
        }

        // Reading file, adding lines to the list

        while (file.hasNext()) {
            list.add(file.nextLine());
        }

        // Sorting the list, writing it to console
        Collections.sort(list);
        System.out.println(list);

    }     
}