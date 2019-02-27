/**
 * Created by lee2173 on 10/29/15.
 */
public class main {

    public static void main(String[] args) {
        try {

            Runnable r1 = new Divider(1, 1000);
            Thread t1 = new Thread(r1);
            t1.start();
            t1.join();
            Runnable r2 = new Divider(1001, 2000);
            Thread t2 = new Thread(r2);
            t2.start();
            t2.join();
            Runnable r3 = new Divider(2001, 3000);
            Thread t3 = new Thread(r3);
            t3.start();
            t3.join();

        }catch(InterruptedException e) {
            System.out.println("Big Problem");
        }

        System.out.println(Divider.counter);

    }
}
