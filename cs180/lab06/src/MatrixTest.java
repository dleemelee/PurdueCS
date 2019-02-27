import static org.junit.Assert.*;
import org.junit.*;

/**
 * Created by lee2173 on 10/1/15.
 */
public class MatrixTest {
    private Matrix myM;
   // private int[][] matrix1;
    //private int[][] matrix2;
    //private int[][] matrix3;

    @Before
    public void setUp() throws Exception {
        myM = new Matrix();
       /** matrix1 = new int[4][4];
        for (int i = 0; i < matrix1.length; i++) {
            for (int j = 0; j < matrix1[0].length; j++) {
                if( i == j) {
                    matrix1[i][j] = 1;
                }
            }
        }
        matrix2 = new int[6][6];
        for (int i = 0; i < matrix2.length; i++) {
            for (int j = 0; j < matrix2[0].length; j++) {
                matrix2[i][j] = i;
            }
        }
        matrix3 = new int[3][4];
        for (int i = 0; i < matrix3.length; i++) {
            for (int j = 0; j < matrix3[0].length; j++) {
                if( i == j) {
                    matrix3[i][j] = 1;
                }

            }
        } **/
    }

    @Test(timeout = 100)
    public void testIsSymmetric1() {
        int[][] matrix1 = { {1,2,2,2}, {2,1,2,2}, {2,2,1,2}, {2,2,2,1} };
        assertEquals(true , myM.isSymmetric(matrix1));
    }

    @Test(timeout = 100)
    public void testIsSymmetric2() {
        int[][] matrix2 = {
                {1,2,3,4},
                {1,2,3,4},
                {1,2,3,4} };
        assertEquals(false , myM.isSymmetric(matrix2));
    }

    @Test(timeout = 100)
    public void testIsSymmetric3() {
        int[][] matrix3 = {
                {2,2,2},
                {3,3,3},
                {4,4,4} };
        assertEquals(false , myM.isSymmetric(matrix3));
    }

    @Test(timeout = 100)
    public void testIsDiagonal1() {
        int[][] matrix1 = { {1,0,0}, {0,1,0}, {0,0,1} };
        assertEquals(true , myM.isDiagonal(matrix1));
    }
    @Test(timeout = 100)
    public void testIsDiagonal2() {
        int[][] matrix2 = { {1,2,0}, {2,1,0}, {0,2,1} };
        assertEquals(false , myM.isDiagonal(matrix2));
    }
    @Test(timeout = 100)
    public void testIsDiagonal3() {
        int[][] matrix3 = { {2,0,0,0}, {0,3,0,0}, {0,0,4,0} };
        assertEquals(true , myM.isDiagonal(matrix3));
    }

    @Test(timeout = 100)
    public void testIsIdentity1() {
        int[][] matrix1 = { {1,0,0}, {0,1,0}, {0,0,1} };
        assertEquals(true , myM.isIdentity(matrix1));
    }
    @Test(timeout = 100)
    public void testIsIdentity2() {
        int[][] matrix2 = { {1,2,3}, {4,5,6}, {7,8,9} };
        assertEquals(false , myM.isIdentity(matrix2));
    }
    @Test(timeout = 100)
    public void testIsIdentity3() {
        int[][] matrix3 = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0} };
        assertEquals(false , myM.isIdentity(matrix3));
    }

    @Test(timeout = 100)
    public void testIsUpperTriangular1() {
        int[][] matrix1 = {
                {1,1,1,1},
                {0,1,1,1},
                {0,0,1,1},
                {0,0,0,1} };
        assertEquals(true , myM.isUpperTriangular(matrix1));
    }
    @Test(timeout = 100)
    public void testIsUpperTriangular2() {
        int[][] matrix2 = { {1,2,3,4},
                            {0,0,0,0},
                            {0,0,0,0} };
        assertEquals(false , myM.isUpperTriangular(matrix2));
    }
    @Test(timeout = 100)
    public void testIsUpperTriangular3() {
        int[][] matrix3 = {
                {1,2,3,4},
                {1,2,3,4},
                {0,1,2,3},
                {0,0,1,2} };
        assertEquals(false , myM.isUpperTriangular(matrix3));
    }

    @Test(timeout = 100)
    public void testIsTridiagonal1() {
        int[][] matrix1 = {
                {1,2,0,0,0},
                {1,2,3,0,0},
                {0,1,2,3,0},
                {0,0,1,2,3},
                {0,0,0,4,5} };
        assertEquals(true , myM.isTridiagonal(matrix1));
    }
    @Test(timeout = 100)
    public void testIsTridiagonal2() {
        int[][] matrix2 = {
                {1,2,3,4,5},
                {1,2,3,4,5},
                {1,2,3,4,5},
                {1,2,3,4,5},
                {1,2,3,4,5} };
        assertEquals(false , myM.isTridiagonal(matrix2));
    }
    @Test(timeout = 100)
    public void testIsTridiagonal3() {
        int[][] matrix3 = {
                {1,2,3,4},
                {1,2,3,4},
                {1,2,3,4} };
        assertEquals(false , myM.isTridiagonal(matrix3));
    }



}
