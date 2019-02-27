import java.util.Scanner;

/**
 * Created by lee2173 on 9/24/15.
 */
public class MathToolsClient {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);



        boolean stay = true;
        while (stay == true) {
            System.out.println("Select a number from the menu choices: ");
            System.out.println("1 - Absolute Value");
            System.out.println("2 - Power");
            System.out.println("3 - Nth Root");
            System.out.println("4 - Scientific Notation");
            int n = input.nextInt();
            switch (n) {
                case 1:

                    System.out.println("Enter value: ");
                    double value = input.nextDouble();
                    System.out.println("The absolute value of " + value + "is: " + MathTools.absoluteValue(value));
                    break;
                case 2:
                    System.out.println("Enter base: ");
                    double base = input.nextDouble();
                    System.out.println("Enter exponent: ");
                    int exponent = input.nextInt();
                    System.out.println("The " + exponent + "th power of " + base + " is: " + MathTools.power(base,
                            exponent));
                    break;
                case 3:
                    System.out.println("Enter the value: ");
                    double val = input.nextDouble();
                    System.out.println("Enter the root: ");
                    int root = input.nextInt();
                    System.out.println("The " + "th" + "root of " + "is: " + MathTools.nthRoot(val, root));
                    break;
                case 4:
                    System.out.println("Enter value: ");
                    double v;
                    v = input.nextDouble();
                    System.out.println("The scientific notation of " + v + "is: " + MathTools.scientificNotation(v));
                    break;
                default:
                    System.out.println("INVALID OPTION");
                    break;
            }
            input.nextLine();
            System.out.println("Retrun to menu? (yes/no)");
            stay = input.nextLine().equalsIgnoreCase("yes") ? true : false;

        }
    }

}
