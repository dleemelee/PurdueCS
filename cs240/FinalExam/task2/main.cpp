/*******************************************************
 * For the detailed Task description, go to MyVector.h *
 *******************************************************/

#include <iostream>
#include <exception>
#include <stdlib.h>
#include "MyVector.h"
#include "MyException.h"

using namespace std;

/*
 * Assignment of MyVector Objects. 
 * A = [1, 2, 3]
 * B = A;
 * Contents of A gets copied to B (deep-copy).
 */
int test_assign0() 
{
	int 		array[5] = {1, 2, 3, 4, 5};

	MyVector	a(5, array);
	MyVector	b;

	b = a;

	b.print();
	return 0; 
}

/* Chained Assignment
 * Example: 
 * 	A = [1, 2, 3]
 * 	B = C = D = A;
 * 	Now A, B, C, D should be [1, 2, 3]
 */
int test_assign1() { 
	int 		array[5] = {1, 2, 3, 4, 5};

  MyVector	a(5, array);
	MyVector	b,c,d;
	
	b=c=d=a; 

	b.print();
	return 0; 
}

/* Vector-Vector multiplication. Example is given below.
 *
 * If vectors A and B are of same length then
 * Each element of A will get multiplied with 
 * corresponding element in vector B
 * 	Example: 
 * 	A = [1, 2, 3]
 * 	B = [4, 3, 100]
 * 	C = a*b; // => [1*4, 2*3, 3*100]
 *
 * 	Now, C will be [4, 6, 300]
 */

int test_mult() { 
	int 		array[5] = {1, 2, 3, 4, 5};

	MyVector	a(5, array);
	MyVector	b(5, array);
	MyVector	c;

	try 
  {
		c = (a * b);
		c.print();
	} 
	catch (MyException &e)
	{
		cout << e.what();
	}	

	return 0; 
}


/* Scalar-Vector Multiplication. 
 * A scalar value is multiplied to a vector on the left. 
 * Example: 
 * 	A = [1, 2, 3]
 * 	scalar = 4
 * 	B = (scalar * b); => Observe that the scalar is on the LEFT of *, not right.
 * 	Now, B will be [4, 8, 12].
 */
int test_sc_mult() 
{ 
	int 		array[5] = {1, 2, 3, 4, 5};

	MyVector	a(5, array);

	a = (-1 * a);
	a.print();

	return 0; 
}

/* Exception Handling. 
 * Vector of length 3 is multiplied with Vector of length 4.  
 * Example: 
 * 	A = [1, 2, 3]
 * 	B = [9, 8, 7, 6]
 * 	C = A * B
 * 	Results in exception of type MyException.
 */
int test_exception() 
{ 
	int 		array0[5] = {1, 2, 3, 4, 5};
	int 		array1[4] = {1, 2, 3, 4};

	MyVector	a(5, array0);
	MyVector	b(4, array1);

  try
  {
    MyVector c = (a * b);
	  c.print();
  }

  catch(MyException &e)
  {
    cout << e.what();
  }

	return 0; 
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
      cout << "Usage: ./task2 <Test Case Number>" << endl;
      cout << "Test case number is the switch() case option in the main()" << endl;
      return 0;
  }

	switch (atoi(argv[1]))
	{
		case 0:
			test_assign0(); /* Test 0: Assignment test */
			break;
	
    case 1: 
			test_assign1(); /* Test 1: Chained Assignment test*/
			break;
		
    case 2: 
			test_mult(); /* Test 2: Vector-Vector multiplication*/
			break;
		
    case 3:
			test_sc_mult(); /* Test 3: Scalar-Vector multiplication*/
			break;
    
    case 4:
			test_exception(); /* Test 4: Exception test */
			break;
    
    /* Add your own test cases here, and invoke them by passing
     * command line arguments to the main() function */

    default:
			break;
	}

	return 0;
}
