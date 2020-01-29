#include<stdio.h>

/*
1 <= i <= j <= n

Ai * Aj
Ai’s dimensions = p[i-1] * p[i]

m[i,j] = m[i,k] + m[k+1,j] + ( p[i-1] * p[k] * p[j] )
*/

#define NUM_MATRICES 4

void bottom_up_matrix_chain_multiply(int dimension[])
{
    int i, j, k, len, mul;
    int n = NUM_MATRICES;
    
    // dimension array has size=(num_matrices+1)
    
    // i goes from 1 to num_matrices - 1
    // j goes from 2 to num_matrices
    // but we still allocate j for the sake for avoiding index manipulation (index-1)
    int optimal_multiplications[NUM_MATRICES][NUM_MATRICES] = {0};
    int optimal_parenthesis[NUM_MATRICES-1][NUM_MATRICES] = {0};
    
    for (len = 2; len <= n; len++)
    {
        for (i = 0; i < (n - len + 1); i++)
        {
            j = i + len - 1;
            
            optimal_multiplications[i][j] = 2147483647; 

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

    printf("optimal_multiplications: \n");
    for (i = 0; i < NUM_MATRICES; i++)
    {
        for (j = 0; j < NUM_MATRICES; j++)
        {
            printf("%d ", optimal_multiplications[i][j]);
        }
        printf("\n");
    }
    
    printf("optimal_parenthesis: \n");
    for (i = 0; i < NUM_MATRICES-1; i++)
    {
        for (j = 0; j < NUM_MATRICES; j++)
        {
            printf("%d ", optimal_parenthesis[i][j]);
        }
        printf("\n");
    }
}

void top_down_mem_matrix_chain_multiply()
{
    
}

int main(void) {
    
    int dimension[NUM_MATRICES+1] = {10, 20, 30, 40, 30};
    bottom_up_matrix_chain_multiply(dimension);
    return 0;
}

