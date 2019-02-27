/**
 * Created by lee2173 on 10/1/15.
 */
public class Matrix {

    public boolean isSymmetric(int[][] matrix) {

        if( matrix.length == matrix[0].length ) {
              for( int i = 0; i < matrix.length; i++ ) {
                  for( int j = 0; j < matrix[0].length; j++ ) {
                      if(matrix[i][j] != matrix[j][i]) {
                          return false;
                      }
                  }
              }
            return true;
        }
        return false;
    }

    public boolean isDiagonal(int [][] matrix)
    {
        for( int i = 0; i < matrix.length; i++ ) {
            for (int j = 0; j < matrix[0].length; j++) {
                if( i != j ) {
                    if( matrix[i][j] != 0 ) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean isIdentity(int[][] matrix) {
        if( matrix.length == matrix[0].length ) {
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    if( i == j) {
                        if( matrix[i][j] != 1 )
                            return false;
                    }
                    else{
                        if( matrix[i][j] !=0 )
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    public boolean isUpperTriangular(int[][] matrix) {
        if( matrix.length == matrix[0].length) {
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    if( i > j ) {
                        if( matrix [i][j] != 0)
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    public boolean isTridiagonal(int[][] matrix) {
        if( matrix.length == matrix[0].length) {
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    if( !(i == j || i+1 == j || j+1 == i) ) {
                        if( matrix [i][j] != 0 ) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }

}
