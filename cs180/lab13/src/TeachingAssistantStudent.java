import java.util.HashMap;
import java.util.Set;

public class TeachingAssistantStudent extends Student {

	private int hours; // total hours of TA
	protected HashMap<String, Integer> courseHour = new HashMap<String, Integer>();

	public TeachingAssistantStudent(String name, String address) {
		super(name, address);
		this.hours = 0;
	}

	// It adds a course into the HashMap with the key of course and hours as the
	// value.
	// This method throws ArrayElementException when the course that is being
	// added to the HashMap already exists in it.
	public void addCourseHour(String course, int hours)
			throws ArrayElementException {
		if( courseHour.get(course) == null) {
			courseHour.put(course, hours);
			this.hours += hours;
		}
		else{
			throw new ArrayElementException("Course Already in List!");
		}


	}

	// This method first should print the courses along with the grades that the
	// TA is taking as a student and then print out the courses with the
	// corresponding hours which the TA is assisting in each line.
	// Use Iterator to iterate the HashMap.
	@Override
	public void printCourses() {
		Set courses = courseHour.keySet();
		System.out.println("CourseName\tCourseGrade\nCoursesAssisting\tHours");
		for( Object eachCourse : courses ) {
			System.out.println(eachCourse.toString() + "\t" + courseHour.get(eachCourse));
		}




	}

	public int getHours() {
		return hours;
	}

	public void setHours(int hours) {
		this.hours = hours;
	}

	@Override
	public String toString() {
		return super.toString() + " Also serving as Teaching Assistant.";
	}

}