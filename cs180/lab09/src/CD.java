/**
 * Created by lee2173 on 10/22/15.
 */
public class CD extends AudioProduct {

    double price;



    CD(String productName, int totalSongs, double price) {
        super(productName, totalSongs);
        this.price = price;
    }

    @Override
    double getPrice() {
        return price;
    }
}
