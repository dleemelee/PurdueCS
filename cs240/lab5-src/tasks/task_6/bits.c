#include "bits.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// It prints the bits in bitmap as 0s and 1s.
// You have to print two lines
// The first line prints the binaries and a new line
// The second line prints "10987654321098765432109876543210\n"
// Ex:
// 00000000000000000000000000000000
// 10987654321098765432109876543210
//
void printBits(unsigned int bitmap)
{
	// Add your code here
	unsigned int size = sizeof(unsigned int);
	unsigned int maxPow = 1<<(size*8-1);
	int i;
	for(i = 0; i<size*8; ++i) {
	    printf("%u", bitmap&maxPow?1:0);
	    bitmap = bitmap<<1;
	}
	printf("\n");
	int j = 31;
	while(j>=0) {
	    printf("%d", j %10);
	    j--;
	}
	printf("\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
// i's range is 0-31
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	// Add your code here
	if(bitValue == 1) {
	    *bitmap |= 1 <<i;
	}
	else{
	    *bitmap &= ~(1<<i);
	}
}

// It returns the bit value (0 or 1) at bit i
// i's range is 0-31
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
	int k;
	k = bitmap >> i;
	if(k&1){
		return 1;
	}
	return 0;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
    int i;
    int count = 0; 
    for(i = 0; i < 32; i++){
	if((bitmap%2==bitValue)){
	    count++;
	}
	bitmap = bitmap >> 1;
    }
    return count;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
    // Add your code here
    int k,i;
    int c = 0;
    int max = 0;
    int index = 0;
    for(i = 31;i>=0;i--){
	k = bitmap >> i;
	if((k&1)){
	    c++;
	}
	else if(!(k&1)){
	    if(c > max){
		max = c;
		index = i;
	    }
		c = 0;
	}
    }
    *position = index+1;
    return max;
}
