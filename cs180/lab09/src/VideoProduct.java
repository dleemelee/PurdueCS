/**
 * Created by lee2173 on 10/22/15.
 */
public abstract class VideoProduct extends Product {

    VideoType type;

    VideoProduct(String productName, VideoType type){
        super(productName);
        this.type = type;
    }


    public VideoType getType() {
        return this.type;
    }
}
