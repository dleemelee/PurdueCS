import java.io.File;
import java.util.Arrays;

/**
 * Created by lee2173 on 12/10/15.
 */
public class Recursion {

    public static int determinant ( int[][] matrix ) {
        if( matrix.length == 1 && matrix[0].length == 1 ) {
            return matrix[0][0];
        }
        else {
            int result = 0;
            for ( int i = 0; i < matrix[0].length; i++ ) {
                int[][] A = new int[matrix.length-1][matrix.length-1];
                int matrixj = 0;
                for ( int j = 1; j < matrix.length; j++) {
                    int matrixk = 0;
                    for ( int k = 0; k < matrix[0].length; k++) {
                        if (k != i) {
                            A[matrixj][matrixk] = matrix[j][k];
                            matrixk++;
                        }
                    }
                    matrixj++;
                }
                if( i % 2 == 0 ) {
                    result = result + (matrix[0][i] * determinant(A));
                }
                else {
                    result = result - (matrix[0][i] * determinant(A));
                }

            }
            return result;
        }

    }

    public static int filecount ( File f ) {

        int count = 0;

        if(f.isFile()) {
            return 1;
        }

        File[] filesList = f.listFiles();
        for( File eachFile : filesList ) {
            count += filecount(eachFile);
        }
        return count;
    }

}
