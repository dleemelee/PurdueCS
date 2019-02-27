import javax.swing.JOptionPane;
/**
 * Created by lee2173 on 11/5/15.
 */
public class FAFSAGUI {
    public static void main(String[] args) {

        boolean cont = false;

        do{
            JOptionPane.showMessageDialog(null, "Welcome to the FAFSA!", "Welcome", JOptionPane.INFORMATION_MESSAGE);

            int isAcceptedInt = JOptionPane.showOptionDialog(null, "Have you been accepted into a degree or " +
                            "certificate program?", "Program Acceptance",
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
            System.out.println(isAcceptedInt);
            boolean isAccepted = FAFSA.yesNoToBool(isAcceptedInt);

            int isRegisteredInt = JOptionPane.showOptionDialog(null, "Are you registered for the selective service?",
                    "Selective Service",
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
            boolean isRegistered = FAFSA.yesNoToBool(isRegisteredInt);

            int hasSSNInt = JOptionPane.showOptionDialog(null, "Do you have a social security number?", "Social " +
                            "Security Number",
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
            boolean hasSSN = FAFSA.yesNoToBool(hasSSNInt);

            int hasValidResidencyInt = JOptionPane.showOptionDialog(null, "Do you have valid residency status?",
                    "Residency Status", JOptionPane.YES_NO_OPTION
                    , JOptionPane.QUESTION_MESSAGE, null, null, null);
            boolean hasValidResidency = FAFSA.yesNoToBool(hasValidResidencyInt);

            int age;
            boolean ageNotTrue = false;
            do{
                String ageString = JOptionPane.showInputDialog(null, "How old are you?", "Age", JOptionPane
                        .QUESTION_MESSAGE);
                age = Integer.parseInt(ageString);
                if( age < 0 ) {
                    JOptionPane.showMessageDialog(null, "Age cannot be a negative number", "Age" , JOptionPane.ERROR_MESSAGE);
                    ageNotTrue = true;
                }else{
                    ageNotTrue = false;

                }
            }while(ageNotTrue);


            int credit;
            boolean creditHoursNotTrue = false;
            do {
                String creditString = JOptionPane.showInputDialog(null, "How many credit hours do you plan on taking?",
                        "Credit Hours", JOptionPane.QUESTION_MESSAGE);
                credit = Integer.parseInt(creditString);
                if( credit < 1 || credit > 24 ){
                    JOptionPane.showMessageDialog(null, "Credit hours must be between 1 and 24, inclusive", "Error: " +
                            "Credit Hours", JOptionPane.ERROR_MESSAGE);
                    creditHoursNotTrue = true;
                }
                else{
                    creditHoursNotTrue = false;
                }
            }while(creditHoursNotTrue);

            int studentIncome;
            boolean StudentIncomeNotTrue = false;
            do {
                String studentIncomeString = JOptionPane.showInputDialog(null, "What is your total yearly income?",
                        "Student Income", JOptionPane
                        .QUESTION_MESSAGE);
                studentIncome = Integer.parseInt(studentIncomeString);
                if( studentIncome < 0 ) {
                    JOptionPane.showMessageDialog(null, "Income cannot be a negative number", "Error: Student " +
                            "Income", JOptionPane.ERROR_MESSAGE);
                    StudentIncomeNotTrue = true;
                }
                else{
                    StudentIncomeNotTrue = false;
                }
            }while(StudentIncomeNotTrue);

            int parentIncome;
            boolean ParentIncomeNotTrue = false;
            do {
                String parentIncomeString = JOptionPane.showInputDialog(null, "What is your parent's total yearly income?", "Parent Income", JOptionPane
                        .QUESTION_MESSAGE);
                parentIncome = Integer.parseInt(parentIncomeString);
                if( parentIncome < 0 ) {
                    JOptionPane.showMessageDialog(null, "Income cannot be a negative number", "Error: Parent " +
                            "Income", JOptionPane.ERROR_MESSAGE);
                    ParentIncomeNotTrue = true;
                }
                else{
                    ParentIncomeNotTrue = false;
                }
            }while(ParentIncomeNotTrue);

            int isDependentInt = JOptionPane.showOptionDialog(null, "Are you dependent?", "Dependency", JOptionPane
                    .YES_NO_OPTION, JOptionPane
                    .QUESTION_MESSAGE, null, null, null);
            boolean isDependent = FAFSA.yesNoToBool(isDependentInt);

            String classStanding;
            String[] cs = {"Freshman" , "Sophomore", "Junior", "Senior", "Graduate"};
            String s = (String)JOptionPane.showInputDialog(null, "What is your current class standing?", "Class Standing",
                    JOptionPane.PLAIN_MESSAGE, null, cs ,null );
            if( s == "Graduate"){
                classStanding = "Graduate";
            }
            else{
                classStanding = "Undergraduate";
            }

            //CREATE FAFSA OBJECT
            FAFSA myF = new FAFSA(isAccepted, isRegistered, hasSSN, hasValidResidency, isDependent, age, credit,
                    studentIncome, parentIncome, classStanding);

            //CALCULATE
            double loan = myF.calcStaffordLoan();
            double grant = myF.calcFederalGrant();
            double workstudy = myF.calcWorkStudy();


            if(myF.calcFederalAidAmount() == 0) {
                loan = grant = workstudy = 0;
            }
            String result = "Loans: " + loan + "\nGrants: " +grant +
                    "\nWorkStudy: " + workstudy + "\n--------------\nTotal: " + myF.calcFederalAidAmount();

            //Display Awards

            JOptionPane.showMessageDialog(null, result, "FAFSA results" , JOptionPane.INFORMATION_MESSAGE);


            //CONTINUE
            int contInt = JOptionPane.showOptionDialog(null, "Would you like to complete another application?",
                    "Continue" ,
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
            cont = FAFSA.yesNoToBool(contInt);

        }while(cont);





    }
}
