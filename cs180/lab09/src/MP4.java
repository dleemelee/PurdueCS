/**
 * Created by lee2173 on 10/22/15.
 */
public class MP4 extends VideoProduct implements  Downloadable {


    MP4(String productName, VideoType type){
        super(productName, type);
    }


    @Override
    public String generateDownloadCode() {
        return null;
    }

    @Override
    double getPrice() {

        if(type == VideoType.MOVIE)
            return 4.99;

        else if(type == VideoType.TVSERIES)
            return 19.99;

        return 0;
    }
}
