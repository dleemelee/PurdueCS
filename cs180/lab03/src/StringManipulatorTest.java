import org.junit.*;

import static org.junit.Assert.*;


/**
 * Created by lee2173 on 9/10/15.
 */
public class StringManipulatorTest {

    private StringManipulator sm;

    @Before
    public void setUp() throws Exception{
        sm = new StringManipulator();
    }

    @Test(timeout = 100)
    public void testMakeUserNameBasic(){
        String ret = sm.makeUserName("john doe");
        String message = "makeUserName():check if username follows the basic Unix style structure";
        assertEquals(message, "jdoe", ret);
    }

    @Test(timeout = 100)
    public void testMakeUserNameLower(){
        String ret = sm.makeUserName("John Doe");
        String message = "makeUserName(): check if username follows the basic Unix style structure";
        assertEquals(message, "jdoe", ret);
    }

    @Test(timeout = 100)
    public void testMakeEmail(){
        String ret = sm.makeEmail(sm.makeUserName("JOHn Nash"), "purdue.edu");
        String message = "makeUserName(): check if email follows the basic Unix style structure";
        assertEquals(message, "jnash@purdue.edu", ret);
    }
}