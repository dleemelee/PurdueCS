
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 *  Please write down a typedef of the following three comparing 
 *  functions: ascending_order, descending_order, special_order.
 *  The type name should be CMP_FUNC.
 */
//typedef CMP_FUNC

/*
 *  Do not modify these comparing functions
 */ 
int ascending_order(int a, int b)
{
    return (a-b);
}
typedef int(*CMP_FUNC)(int, int);
CMP_FUNC f1 = &ascending_order;
int descending_order(int a, int b)
{
    return (b-a);
}
CMP_FUNC f2 = &descending_order;
int special_order(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    return (a%b);
}
CMP_FUNC f3 = &special_order;
/*
 *  Please implement the bubble sort function that uses
 *  the CMP_FUNC to do the sorting.
 *
 *  Do the bubble sort from the index 0 of the array 'numbers'.
 *  Compare each pair of neighboring elements in the array
 *  and swap them if cmp(a, b) is larger than 0,
 *  where the index of a in 'numbers' is smaller than b
 *
 */
void swap(int *n1, int *n2) {
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
void bubble_sort(int *numbers, int count, CMP_FUNC cmp)
{
	int i,j;
	for(i = 0; i < count; i++){
	    for(j = 0; j < count-1; j++) {
		if(cmp(numbers[j], numbers[j+1])>0){
		    swap(&numbers[j], &numbers[j+1]);
		}
	    }
	}

}


/*
 *  Do NOT change the code between here and the end of the file.
 */
void print_numbers(int *numbers, int len)
{
    int i = 0;

    if (numbers == NULL) {
        return;
    }

    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char *usage = "sort_array <numbers>\nE.g., sort_array 1 2 5 4 3\n";
    int count = argc - 1;
    int *numbers = NULL;
    int i = 0;

    if (argc < 2) {
        printf("%s", usage);
        exit(1);
    }
    
    numbers = (int*)malloc((argc-1) * sizeof(int));
    assert(numbers != NULL);

    for (i = 0; i < count; i++) {
        *(numbers+i) = atoi(argv[i+1]);
    }
    
    printf("Original: ");
    print_numbers(numbers, count);

    bubble_sort(numbers, count, ascending_order);
    printf("Ascending: ");
    print_numbers(numbers, count);
    
    bubble_sort(numbers, count, descending_order);
    printf("Descending: ");
    print_numbers(numbers, count);
    
    bubble_sort(numbers, count, special_order);
    printf("Special: ");
    print_numbers(numbers, count);

    free(numbers);

    return 0;
}



