/**
 * Created by lee2173 on 10/22/15.
 */
public abstract class Product {

    String productName;

    Product(String productName){
        this.productName = productName;
    }

    String getProductName(){
        return this.productName;
    }

    abstract double getPrice();


}
