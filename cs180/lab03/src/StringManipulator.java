import java.util.Scanner;
/**
 * CS180 - Lab 03 - StringManipulator
 *
 * (Takes in a full name, creates an ID and sticks it with an email domain)
 *
 * @author David Lee lee2173@purdue.edu
 */



public class StringManipulator {

    private StringManipulator sm;


    /*
    takes in the full name of the user, and returns their username
     */
    public String makeUserName(String fullName){
        if(fullName == null){
            return null;
        }
        int space = fullName.indexOf(' ');
        String userName = fullName.substring(0,1)+fullName.substring(space+1, fullName.length());
        return userName.toLowerCase();
    }




    /*
    takes in the username and the domain of the user and returns the email address
     */
    public String makeEmail(String userName, String domain){
        if(userName == null || domain == null ){
            return null;
        }
        domain = domain.toLowerCase();
        return userName + "@" + domain;
    }



    public static void main(String[] args) {
        Scanner myS = new Scanner(System.in);
        StringManipulator mySM = new StringManipulator();
        System.out.println("Enter the Full Name of the person followed by the Last Name: ");
        String fullName = myS.nextLine();
        System.out.println("Enter the domain Name: ");
        String domainName = myS.nextLine();
        System.out.print("The user name for the person is:  ");
        System.out.println(mySM.makeUserName(fullName));
        System.out.print("The email id for the person is: ");
        System.out.println(mySM.makeEmail(mySM.makeUserName(fullName), domainName));
    }

}
