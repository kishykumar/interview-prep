// Quick sort
// Pick a pivot and then place it at the right position.
// https://www.khanacademy.org/computing/computer-science/algorithms/quick-sort/a/overview-of-quicksort

#include <stdio.h>

void swap(int array[], int i, int j)
{
    int k = array[i];
    array[i] = array[j];
    array[j] = k;
}

// This function partitions given array and returns 
//  the index of the pivot.
int partition(int array[], int p, int r)
{
    int left_i = p, right_i = r;
    int pivot_i = r;
    
    // Move the pivot to the correct position
    while (pivot_i != left_i)
    {
        if (array[pivot_i - 1] < array[pivot_i])
        {
            swap(array, left_i, pivot_i - 1);
            left_i++;
        }
        else
        {
            swap(array, right_i, pivot_i - 1);
            
            pivot_i--;
            right_i--;
        }
    }
    
    return pivot_i;
}

void quickSort(int array[], int p, int r) 
{
    int pivot_i;
    
    // Base case: if #elements in the array is 0 or 1, exit
    if ((r-p) < 1)
        return;
    
    // divide (partition)
    pivot_i = partition(array, p , r);

    // conquer: recursively go on left and right side of the array
    if (pivot_i != p)
        quickSort(array, p , pivot_i - 1);
    
    if (pivot_i != r)
        quickSort(array, pivot_i + 1, r);
}

int main() {
    
    int i = 0;
	int unsorted_array[] = {9, 7, 5, -1, 2, 2, 14, 3, 0, 3};
	int arr_size = sizeof(unsorted_array) / sizeof(int);
	
	quickSort(unsorted_array, 0, arr_size -1);
    
    for (i = 0; i < arr_size; i++)
        printf("%d ", unsorted_array[i]);
        
    printf("\n");
    
    // Program.assertEqual(array, [2,3,5,6,7,9,10,11,12,14]);

	return 0;
}