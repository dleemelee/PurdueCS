/**
 * Created by lee2173 on 10/22/15.
 */
public abstract class AudioProduct extends Product {

    int totalSongs;

    AudioProduct(String productName) {
        super(productName);
    }

    AudioProduct( String productName, int totalSongs){
        super(productName);
        this.totalSongs = totalSongs;
    }

    public int getTotalSongs() {
        return totalSongs;
    }


}
