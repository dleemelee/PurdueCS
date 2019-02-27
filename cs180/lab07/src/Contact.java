/**
 * Created by lee2173 on 10/8/15.
 */
public class Contact {
    String name;
    long number;
    String address;

    //one String
    public Contact(String name) {
        this.name = name;
    }

    public Contact(String name, long number) {
        this(name);
        this.number = number;
    }

    public Contact(String name, long number, String address) {
        this(name, number);
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getNumber() {
        return number;
    }

    public void setNumber(long number) {
        this.number = number;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
