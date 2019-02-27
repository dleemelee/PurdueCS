/**
 * Created by lee2173 on 9/3/15.
 */
import java.util.Scanner;

public class PythagorasClient {
    public static void main(String[] args){
        Scanner myS = new Scanner(System.in);
        Pythagoras myP = new Pythagoras();
        System.out.print("Enter the length of side 'A': ");
        int sideA = myS.nextInt();
        System.out.print("Enter the length of side 'B': ");
        int sideB = myS.nextInt();
        double hypotenuse = myP.getHypotenuse(sideA, sideB);
        System.out.println("Side A: " + sideA);
        System.out.println("Side B: " + sideB);
        System.out.println("Hypotenuse: " + hypotenuse);
    }
}
