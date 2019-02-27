/**
 * Created by lee2173 on 10/29/15.
 */
public class Driver {

    public static void main(String[] args) {
        Thread t = new A();
        t.start();
        Runnable r = new B();
        Thread t1 = new Thread(r);
        t1.start();

    }
}
