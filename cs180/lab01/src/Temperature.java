import java.util.Scanner;
/**
 * Created by lee2173 on 8/27/15.
 */
public class Temperature {
    public static void main(String[] args){
        double fahrenheit;
        double celsius;
        Scanner mys = new Scanner(System.in);
        System.out.println("Enter the temperature in Fahrenheit: ");
        fahrenheit = mys.nextDouble();
        celsius = ((fahrenheit -32) * 5 / 9);
        System.out.println("Fahrenheit: " + fahrenheit);
        System.out.println("Celsius: " + celsius);
        System.out.println("Enter the temperature in Celsius: ");
        celsius = mys.nextDouble();
        fahrenheit = ((celsius * 9) / 5) + 32;
        System.out.println("Fahrenheit: " + fahrenheit);
        System.out.println("Celsius: " + celsius);
    }
}
