#include <stdio.h>

#include "array.h"

// Return sum of the array
// Return zero if inputs are invalid
double sumArray(int n, double * array) {
    // Add your code here
    if(n<0 || array == NULL) {
	return 0;
    }
    int i = 0;
    double sum = 0;
    for(i = 0; i < n; i++)
    {
	sum += *(array+i);	
    }
    return sum;
}

// Return maximum element of array
// If the inputs are invalid, return 0`
// Note: return its value, not its index
double maxArray(int n, double * array) {
    // Add your code here
    if(n < 0 || array == NULL){
	return 0;
    }
    int i = 0;
    double max = *(array+0);
    for(i = 1 ; i < n; i++) 
    {
    	if(max < *(array+i))
	{
	    max = *(array+i);
	}
    }
    return max;
}

// Return minimum element of array
// If the inputs are invalid, return 0`
// Note: return its value, not its index
double minArray(int n, double * array) {
    // Add your code here
    if(n < 0 || array == NULL) {
	return 0;
    }
    int i = 0;
    double min = *(array+0);
    for(i = 1; i < n; i++)
    {
	if(min > *(array+i)) {
	    min = *(array+i);
	}
    }
    return min;
}

// Find the position in the array of the first element 
// whose value is min<=x<=max.
// Return -1 if no element was found or the inputs are invalid
// Note: return the target's index, not its value
int findArray(int n, double * array, double min, double max) {
    // Add your code here
    if( n < 0 || array == NULL ) {
	return -1;
    }
    int i = 0;
    for(i = 0; i < n; i++) {
    	int temp = *(array+i);
	if( temp < max && temp > min  )
		return i;
    }
    return -1;
}

void swap(double * array, int a, int b){
    double temp = *(array+a);
    *(array+a) = *(array+b);
    *(array+b) = temp;
}

// reverse the elements in the array
// For example,
// an array with values 1,2,3,4,5 (double a[5]={1,2,3,4,5})
// should be converted into
// an array with values 5,4,3,2,1 (double b[5]={5,4,3,2,1})
// If the inputs are invalid, return without changing the array
void reverseArray(int n, double * array) {
    // Add your code here
    if(n < 0 || array == NULL) {
	return;
    }
    int i = 0;
    int j = n-1;
    for(;i<n/2;i++,j--)
    {
	swap(array, i, j);
    }
    
    return;
}

// Print out each element in the array in the following format:
// For an array a[3]={4,3,5}
// the output would be:
// 0:4.000000
// 1:3.000000
// 2:5.000000
// Note that newline should be added at the end of each element.
// If the inputs are invalid, return without changing the array
void printArray(int n, double * array) {
    // Add your code here
    int i = 0;
    if(n < 0 || array == NULL) {
	return;
    }
    for(i = 0; i < n; i++, array++) {
	printf("%d:%lf\n",i,*(array));
    }
}

