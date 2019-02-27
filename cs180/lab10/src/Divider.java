
/**
 * Created by lee2173 on 10/29/15.
 */
public class Divider implements Runnable {

    int start;
    int end;
    static int counter = 0;

    Divider( int start, int end) {
        this.start = start;
        this.end= end;
    }

    public void run() {
        for (int i = start; i <= end; i++) {
            if (i % 7 == 0) {
                increment();
            }
        }
    }

    public static synchronized void increment(){
            counter++;
    }

    public static void main(String[] args) {
        try {

            Runnable r1 = new Divider(1, 1000);
            Thread t1 = new Thread(r1);

            Runnable r2 = new Divider(1001, 2000);
            Thread t2 = new Thread(r2);

            Runnable r3 = new Divider(2001, 3000);
            Thread t3 = new Thread(r3);
            t3.start();
            t1.start();
            t2.start();
            t2.join();
            t1.join();
            t3.join();
        }catch(InterruptedException e) {
            System.out.println("Big Problem");
        }

        System.out.println(Divider.counter);

    }
}




