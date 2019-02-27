/**
 * Created by lee2173 on 9/3/15.
 * This class will make use of the Pythagoras class and make a simple GUI window that can read input from the user
 */
import javax.swing.JOptionPane;


public class PythagorasSimpleGUI {
    public static void main(String[] args) {
        Pythagoras myP = new Pythagoras();
        String input1 = JOptionPane.showInputDialog("Enter the length of side 'A': ");
        int sideA = Integer.parseInt(input1);
        String input2 = JOptionPane.showInputDialog("Enter the length of side 'B': ");
        int sideB = Integer.parseInt(input2);
        double hypotenuse = myP.getHypotenuse(sideA, sideB);
        System.out.println("Side 'A': " + sideA);
        System.out.println("Side 'B': "+ sideB);
        System.out.println("Hypotenuse: " + hypotenuse);
        JOptionPane.showMessageDialog(null, "The hypotenuse is: " + hypotenuse);
    }
}

