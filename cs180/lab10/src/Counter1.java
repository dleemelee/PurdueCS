/**
 * Created by lee2173 on 10/29/15.
 */
public class Counter1 implements Counter {
    int c = 0;

    @Override
    public synchronized void inc() {
        c++;
    }

    @Override
    public synchronized void dec() {
        c--;
    }

    @Override
    public synchronized int get() {
        return c;
    }
}
