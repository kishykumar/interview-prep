// selection algorithm: Find kth smallest element using median of medians
#include <stdio.h>
#include <stdlib.h>

// Q: What change in the code to handle duplicates? 
// - Basic answer is to remove duplicates in linear time (using HT)
// - 

// Q: Test cases? 
// - Ensure full code coverage
// - List has zero elements
// - List is sorted ascending/descending
// - List size is less than 5
// - List size is 5
// - last sublist has 5 elements
// - last sublist has less than 5 elements
// - Print all smallest elements all the time

// Auxilliary Space and Space complexity

void swap(int array[], int i, int j)
{
    int k = array[i];
    array[i] = array[j];
    array[j] = k;
}

// This function partitions given array based on the element at 
// partition_elem_idx and returns the index of the same element after 
// partitioning. 
int partition(int array[], int left, int right, int partition_elem)
{    
    int i = 0; 
    int large_elem_idx = right; // shift the elements larger than partition_elem to the right of the array

    // Move the pivot to the correct position
    while (i != large_elem_idx)
    {
        if (array[i] < partition_elem)
            i++;
        else if (array[i] > partition_elem)
        {
            swap(array, i, large_elem_idx);
            large_elem_idx--;
        }
        else 
            swap(array, i, large_elem_idx);
    }
    
    return i;
}

int compare_ints(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order. 
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order. 

    return 0;
}

int sort_and_med(int array[], int left, int right)
{
    int list_len = (right - left + 1);    // length of the list (#elements)
    int median_index = left + (list_len / 2);

    // confirm that the array length is less than or equal to 5
    if (list_len > 5)
        printf("Trouble! Array length greater than 5: %d\n", list_len);

    qsort(&array[left], list_len, sizeof(int), compare_ints);

    return array[median_index]; 
}

void printArr(int array[], const char *comment)
{
    int i;

    printf("Printing array at %s\n", comment);

    for (i = 0; i < 15; i++)
        printf("%d ", array[i]);

    printf("\n");
}

// @returns approximate median of the input array
int median_of_medians(int array[], int left, int right)
{
    int list_len = (right - left + 1);    // length of the list (#elements)
    int med_arr_len = (list_len + 4) / 5;
    int medians[med_arr_len];              // medians array

    int i = 0;  // array index
    int l;  // left index used for sorting and computing medians

    // Pseudo Code for Finding Median of Medians
    // 1. Split the list into sublists of 5 elements
    // 2. Sort the 5 elements using quicksort
    // 3. Find medians of all these sublists and store them in a temp array
    // 4. Go back to Step 1 recursively

    l = left;
    for (i = 0; (i < med_arr_len) && ((l + 5 - 1) <= right); i++)
    {
        medians[i] = sort_and_med(array, l, l + 5 - 1);
        l += 5;         
    }

    // Handle the last sublist that's less than 5 elements
    if ((list_len / 5) < med_arr_len)
    {
        medians[i] = sort_and_med(array, l, right);
    }

    // Base condition
    if (med_arr_len == 1)
        return medians[0];

    return median_of_medians(medians, 0, med_arr_len - 1);
}

int quickSelect(int array[], int left, int right, int k)
{
    int list_len = (right - left + 1);    // length of the list (#elements)
    int med_of_meds; 
    int med_of_meds_idx; 

    // Pseudo Code
    // 1. Find Median of Medians
    // 2. Partition the array based on median of medians obtained from Step 1. 
    // 3. Get the index of median of medians element in the array - say i
    // 4. - if i == k stop and return element
    //    - if i > k, recurse over quickSelect([left,i-1], k)
    //    - if i < k, recurse over quickSelect([i+1,right], k-i-1)

    med_of_meds = median_of_medians(array, left, right);

    med_of_meds_idx = partition(array, left, right, med_of_meds);

    // Base condition
    if (med_of_meds_idx == k)
        return med_of_meds;
    else if (med_of_meds_idx > k)
        return quickSelect(array, left, med_of_meds_idx - 1, k);
    else
        return quickSelect(array, med_of_meds_idx + 1, right, k);
}

int main() {
    
    int i = 0, k = 0;
    int elem;
	int unsorted_array[] = {14,5,8,3,6,15,0,1,4,12,2,9,7,13,10,11};
	int arr_size = sizeof(unsorted_array) / sizeof(int);

    scanf("%d", &k);

    if (k > arr_size)
    {
        printf("Bad input\n");
        return -1;
    }

	elem = quickSelect(unsorted_array, 0, arr_size - 1, k - 1);
    printf("%dth smallest element is: %d\n", k, elem);

	return 0;
}
