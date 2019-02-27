/**
 * Created by lee2173 on 10/22/15.
 */
import java.util.UUID;

public class MP3 extends AudioProduct implements Downloadable {


    MP3(String productName){
        super(productName);
    }

    @Override
    public String generateDownloadCode() {
        return UUID.randomUUID().toString();
    }

    @Override
    double getPrice() {
        return 0.99;
    }
}
