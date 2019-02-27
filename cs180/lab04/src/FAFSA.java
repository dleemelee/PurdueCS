/**
 * Created by lee2173 on 9/17/15.
 */
public class FAFSA {

    boolean isAcceptedStudent;
    boolean isSSregistered;
    boolean hasSSN;
    boolean hasValidResidency;
    boolean isDependent;
    int age;
    int creditHours;
    double studentIncome;
    double parentIncome;
    String classStanding;

    public FAFSA(boolean isAcceptedStudent, boolean isSSregistered, boolean hasSSN, boolean hasValidResidency,
                 boolean isDependent, int age, int creditHours, double studentIncome, double parentIncome, String classStanding){
        this.isAcceptedStudent = isAcceptedStudent;
        this.isSSregistered = isSSregistered;
        this.hasSSN = hasSSN;
        this.hasValidResidency = hasValidResidency;
        this.isDependent = isDependent;
        this.age = age;
        this.creditHours = creditHours;
        this.studentIncome = studentIncome;
        this.parentIncome = parentIncome;
        this.classStanding = classStanding;

    }

    public boolean isFederalAidEligible(){

        if(!(age > 25 || age < 18)) {
            if (isAcceptedStudent && isSSregistered && hasSSN && hasValidResidency) {
                return true;
            }
        }
        else if((age > 25 || age < 18)) {
             if (isAcceptedStudent && hasValidResidency && hasSSN) {
                return true;
            }
        }
        return false;
    }

    public double calcEFC(){

        if(isDependent){
            return studentIncome + parentIncome;
        }
        return studentIncome;
    }

    public double calcFederalGrant(){

        if(classStanding == null){
            return 0;
        }
        if(isFederalAidEligible() == false){
            return 0;
        }

        else if(classStanding.equalsIgnoreCase("Undergraduate")){
            if(creditHours < 9){
                return 2500;
            }
            return 5775;
        }
        else if(classStanding.equalsIgnoreCase("Graduate")){
            if(creditHours < 9){
                return 0;
            }
            return 0;
        }
        return 0;
    }

    public double calcStaffordLoan(){

        if(classStanding == null){
            return 0;
        }
        if(creditHours >= 9){
            if(classStanding.equalsIgnoreCase("Graduate")){
                if(isDependent){
                    return 10000;
                }
                else
                    return 20000;

            }
            else if(classStanding.equalsIgnoreCase("Undergraduate")){

                if(isDependent){
                    return 5000;
                }
                else
                    return 10000;
            }
        }
        return 0;
    }

    public double calcWorkStudy(){
        double EFC = calcEFC();
        if(EFC <= 30000){
            return 1500;
        }
        else if(EFC <= 40000){
            return 1000;
        }
        else if(EFC <= 50000){
            return 500;
        }
        else if(EFC > 50000){
            return 0;
        }
        return 0;
    }

    public double calcFederalAidAmount(){
        if(!isFederalAidEligible()){
            return 0;
        }
        return calcStaffordLoan() + calcFederalGrant()+ calcWorkStudy();
    }

}
