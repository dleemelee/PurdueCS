/**
 * Created by lee2173 on 9/24/15.
 */
public class MathTools {

    final static double E = 0.000000001;

    public static double absoluteValue(double n) {

        if(n < 0)
            n = -n;

        return n;

    }


    public static double power(double base, int exponent) {

        double total = 1;

        if( exponent < 0 ) {
            base = 1/base;
        }

        for( int i = 0; i < absoluteValue(exponent); i++){
            total *= base;
        }

        return total;

    }


    public static double nthRoot(double value, int root) {

        if(value <= 0 || root == 0){
            return 0.0;
        }

        double xk = 0.0; //initial
        double xkpo = 0.0; //next
        double delta = 1;
        double temp;

        if( root > 0 ) {
            xk = value;

        }

        else {
            xk = 1/value;
        }
        while(delta > E){
            xkpo = (1.0/root) * (((root - 1) * xk) + (value/power(xk,root-1)));
            delta = absoluteValue(xkpo - xk);
            temp = xkpo;
            xkpo = xk;
            xk = temp;

        }

        return xkpo;



    }

    public static String scientificNotation(double n){

        String s = "";
        int counter = 0;
        double n2 = absoluteValue(n);


        if( n2 < 1 ){

            while( n2 < 1 ){
                n *= 10;
                n2 *= 10;
                counter --;
            }


        }

        else if( n2 >= 10 ){
            while( n2 >= 10 ){
                n /= 10.0;
                n2 /= 10.0;
                counter ++;
            }

        }

        n = ((int)(n * 1000000.0)) / 1000000.0;
        s = n + " x 10 ^ " + counter;
        return s;

    }

    public static void main(String[] args) {
        System.out.println(MathTools.nthRoot(16, 4));
    }


}
