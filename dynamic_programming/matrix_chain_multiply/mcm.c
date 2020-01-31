#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/*
1 <= i <= j <= n

Ai * Aj
Ai’s dimensions = p[i-1] * p[i]

m[i,j] = m[i,k] + m[k+1,j] + ( p[i-1] * p[k] * p[j] )
*/

#define  NUM_MATRICES  4
#define  INTMAXVAL     2147483647


void computeBottomUpMatMul(
    int optimal_multiplications[][NUM_MATRICES], 
    int optimal_parenthesis[][NUM_MATRICES], 
    int dimension[], 
    int num_matrices)
{
    int i, j, k, len, mul;
    int n = num_matrices;
    
    // dimension array has size=(num_matrices+1)
    
    // i goes from 1 to num_matrices - 1
    // j goes from 2 to num_matrices
    // but we still allocate j for the sake for avoiding index 
    // manipulation (index-1)
    
    for (len = 2; len <= n; len++)
    {
        for (i = 0; i < (n - len + 1); i++)
        {
            j = i + len - 1;
            optimal_multiplications[i][j] = INTMAXVAL;

            for (k = i; k < j; k++)
            {
                mul = optimal_multiplications[i][k] + 
                      optimal_multiplications[k+1][j] + 
                      (dimension[i] * dimension[k+1] * dimension[j+1]);
                
                if (mul < optimal_multiplications[i][j])
                {
                    optimal_multiplications[i][j] = mul;
                    optimal_parenthesis[i][j] = k;
                }
            }
        }
    }
}

int computeTopDownMatMulHelper(
    int optimal_multiplications[][NUM_MATRICES], 
    int optimal_parenthesis[][NUM_MATRICES], 
    int dimension[], 
    int i,
    int j)
{
    int k;
    int temp_mul;

    /* Use the cached result if it exists */
    if (optimal_multiplications[i][j] != INTMAXVAL)
        return optimal_multiplications[i][j];

    /* Base Condition */
    if (i == j)
    {
        optimal_multiplications[i][j] = 0;
        return 0;
    }

    /* Recursively find the number of multiplications */
    for (k = i; k < j; k++)
    {
        temp_mul = computeTopDownMatMulHelper(optimal_multiplications, 
                                              optimal_parenthesis, 
                                              dimension, i, k) + 
                   computeTopDownMatMulHelper(optimal_multiplications, 
                                              optimal_parenthesis, 
                                              dimension, k+1, j) + 
                   (dimension[i] * dimension[k+1] * dimension[j+1]);

        if (temp_mul < optimal_multiplications[i][j])
        {
            /* Cache the minimum (and finally the optimal) value */
            optimal_multiplications[i][j] = temp_mul;
            optimal_parenthesis[i][j] = k;
        }
    }

    return optimal_multiplications[i][j];
}

void computeTopDownMatMul(
    int optimal_multiplications[][NUM_MATRICES], 
    int optimal_parenthesis[][NUM_MATRICES], 
    int dimension[], 
    int num_matrices)
{
    optimal_multiplications[0][num_matrices-1] = 
        computeTopDownMatMulHelper(optimal_multiplications, 
                                   optimal_parenthesis, 
                                   dimension, 0, num_matrices-1);
}

void print_mcm(int optimal_multiplications[][NUM_MATRICES], 
               int optimal_parenthesis[][NUM_MATRICES], 
               int num_matrices)
{
    int i, j;

    printf("optimal_multiplications: \n");
    for (i = 0; i < num_matrices; i++)
    {
        for (j = 0; j < num_matrices; j++)
        {
            printf("%d ", optimal_multiplications[i][j]);
        }
        printf("\n");
    }
    
    printf("optimal_parenthesis: \n");
    for (i = 0; i < num_matrices-1; i++)
    {
        for (j = 0; j < num_matrices; j++)
        {
            printf("%d ", optimal_parenthesis[i][j]);
        }
        printf("\n");
    }
}

void clear_mcm(int optimal_multiplications[][NUM_MATRICES], 
               int optimal_parenthesis[][NUM_MATRICES], 
               int num_matrices)
{
    int i, j;

    for (i = 0; i < num_matrices; i++)
        for (j = 0; j < num_matrices; j++)
            optimal_multiplications[i][j] = INTMAXVAL;

    for (i = 0; i < num_matrices-1; i++)
        memset(optimal_parenthesis[i], 0, sizeof(int) * num_matrices);
}

// Test Cases: 
// Input: p[] = {40, 20, 30, 10, 30};
// Output: 26000  

// Input: p[] = {10, 20, 30, 40, 30};
// Output: 30000 

int main(void) 
{
    int dimension[NUM_MATRICES+1] = {10, 20, 30, 40, 30};

    int optimal_multiplications[NUM_MATRICES][NUM_MATRICES] = {0};
    int optimal_parenthesis[NUM_MATRICES-1][NUM_MATRICES] = {0};

    /* computeBottomUpMatMul expects all values to be zero */
    computeBottomUpMatMul(optimal_multiplications, optimal_parenthesis, 
                          dimension, NUM_MATRICES);

    print_mcm(optimal_multiplications, optimal_parenthesis, NUM_MATRICES);

    clear_mcm(optimal_multiplications, optimal_parenthesis, NUM_MATRICES);

    /* computeTopDownMatMul expects optimal_multiplications values = INTMAXVAL 
     * and optimal_parenthesis values = 0 that clear_mcm does. 
     */
    computeTopDownMatMul(optimal_multiplications, optimal_parenthesis, 
                         dimension, NUM_MATRICES);

    print_mcm(optimal_multiplications, optimal_parenthesis, NUM_MATRICES);

    return 0;
}

