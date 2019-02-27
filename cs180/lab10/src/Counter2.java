import java.util.concurrent.atomic.AtomicInteger;

/**
 * Created by lee2173 on 10/29/15.
 */
public class Counter2 implements  Counter {
    AtomicInteger c = new AtomicInteger(0);

    @Override
    public void inc() {
        c.addAndGet(1);
    }

    @Override
    public void dec() {
        c.addAndGet(-1);
    }

    @Override
    public int get() {
        return c.get();
    }
}
