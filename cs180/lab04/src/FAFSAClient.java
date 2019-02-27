import java.util.Scanner;

/**
 * Created by lee2173 on 9/17/15.
 */
public class FAFSAClient {

    public static void main(String[] args) {
        Scanner myS = new Scanner(System.in);
        System.out.println("Have you been accepted into a degree or certificate program?");
        String accepted = myS.nextLine();
        boolean isAcceptedStudent;
        if(accepted.equalsIgnoreCase("yes")){
            isAcceptedStudent = true;
        }
        else{
            isAcceptedStudent = false;
        }
        System.out.println("Are you registered for the selective service?");
        boolean isSSRegistered = myS.nextLine().equalsIgnoreCase("yes") ? true : false;
        System.out.println("Do you have a social security number?");
        boolean isSSN = myS.nextLine().equalsIgnoreCase("yes") ? true : false;
        System.out.println("Do you have a valid residency status?");
        boolean isValidResident = myS.nextLine().equalsIgnoreCase("yes") ? true : false;
        System.out.println("How old are you?");
        int age = myS.nextInt();
        System.out.println("How many credit hours do you plan on taking?");
        int creditHours = myS.nextInt();
        System.out.println("What is your total yearly income?");
        double studentIncome = myS.nextDouble();
        System.out.println("What is your parent's total yearly income?");
        double parentDouble = myS.nextDouble();
        myS.nextLine();
        System.out.println("Are you dependent?");
        boolean isDependent = myS.nextLine().equalsIgnoreCase("yes") ? true : false;
        System.out.println("Are you an undergraduate or graduate?");
        String classStanding = myS.nextLine();
        FAFSA myF = new FAFSA(isAcceptedStudent, isSSRegistered, isSSN, isValidResident, isDependent, age, creditHours,
                studentIncome, parentDouble, classStanding);
        System.out.println("Your total estimated aid package is: " + myF.calcFederalAidAmount());


    }
}
