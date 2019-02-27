import java.util.Stack;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by lee2173 on 12/3/15.
 */
public class Evaluator {

    public static double evaluate(String s) {
        Stack<Double> results = new Stack();
        String[] a = s.split(" ");
        double pop1;
        double pop2;
        for( int i = 0; i <  a.length; i++) {
            if( a[i].matches("^-?\\d+$")) {
                results.push(Double.parseDouble(a[i]));
            }
            else if(a[i].equals("+")){
                pop1 = results.pop();
                pop2 = results.pop();
                results.push(pop2 + pop1);
            }
            else if(a[i].equals("-")){
                pop1 = results.pop();
                pop2 = results.pop();
                results.push(pop2 - pop1);
            }
            else if(a[i].equals("*")){
                pop1 = results.pop();
                pop2 = results.pop();
                results.push(pop2 * pop1);
            }
            else if(a[i].equals("/")){
                pop1 = results.pop();
                pop2 = results.pop();
                results.push(pop2 / pop1);
            }
        }
        return results.pop();
    }

    public static void main(String[] args) {
        System.out.println(evaluate("5 1 2 + 4 * + 3 -"));
    }


}
