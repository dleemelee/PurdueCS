/**
 * Created by lee2173 on 10/22/15.
 */
public class DVD extends VideoProduct {

    double price;



    DVD( String productName, VideoType type, double price) {
        super(productName, type);
        this.price = price;
    }

    @Override
    public double getPrice() {
        return price;
    }
}
