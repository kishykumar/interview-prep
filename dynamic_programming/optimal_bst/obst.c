#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define OBST_MAX_ARR_LEN 6

#define INTMAXVAL ((2^31)-1)

typedef int matrix[OBST_MAX_ARR_LEN][OBST_MAX_ARR_LEN];

typedef struct obst_ctx
{
  int   keys_prob[OBST_MAX_ARR_LEN];
  int   dummy_prob[OBST_MAX_ARR_LEN];
  char  *keys[OBST_MAX_ARR_LEN];
  char  *dummy_keys[OBST_MAX_ARR_LEN];

  matrix  roots;
  matrix  cost;
  matrix prob_sum;
} obst_ctx;

void print_obst(obst_ctx *ctx)
{
  int i, j;

  printf("roots: \n");
  for (i = 0; i < OBST_MAX_ARR_LEN; i++)
  {
    for (j = 0; j < OBST_MAX_ARR_LEN; j++)
    {   
      printf("%d ", ctx->roots[i][j]);
    }   
    printf("\n");
  }   
      
  printf("cost: \n");
  for (i = 0; i < OBST_MAX_ARR_LEN; i++)
  {   
    for (j = 0; j < OBST_MAX_ARR_LEN; j++)
    {   
      printf("%d ", ctx->cost[i][j]);
    }   
    printf("\n");
  }   
}

void find_obst(obst_ctx *ctx)
{
  int i, j, r, x;
  int root_index;
  int window_size = 0;
  int temp_cost;
  int left_subtree_cost, right_subtree_cost;

  for (window_size = 0; window_size < OBST_MAX_ARR_LEN; window_size++)
  {
    for (i = 1; i < OBST_MAX_ARR_LEN; i++)
    {
      j = i + window_size;

      /* Continue if j goes over OBST_MAX_ARR_LEN */
      if (j >= OBST_MAX_ARR_LEN)
        continue;

      /* Calculate sum of probabilities between i and j if not already 
       * calculated.
       */
      if (ctx->prob_sum[i][j] ==  0)
      {
        for (x = i; x <= j; x++)
          ctx->prob_sum[i][j] += ctx->keys_prob[x];

        for (x = i - 1; x <= j; x++)
          ctx->prob_sum[i][j] += ctx->dummy_prob[x];
      }

      for (r = i; r <= j; r++)
      {
        /* Special cost of the leftmost and rightmost subtrees */
        if (r == i)
          left_subtree_cost = ctx->dummy_prob[r - 1];
        else
          left_subtree_cost = ctx->cost[i][r - 1];

        if (r == j)
          right_subtree_cost = ctx->dummy_prob[r];
        else
          right_subtree_cost = ctx->cost[r + 1][j];

        temp_cost = left_subtree_cost + right_subtree_cost + 
                    ctx->prob_sum[i][j];

        if (ctx->cost[i][j] > temp_cost)
        {
          ctx->cost[i][j] = temp_cost;
          ctx->roots[i][j] = r;
        }
      }
    }
  }
}

int main(void)
{
  obst_ctx ctx = {
                   {9999999, 15, 10, 5, 10, 20},
                   {5, 10, 5, 5, 5, 10},
                   {"nil", "k1", "k2", "k3", "k4", "k5"},
                   {"d1", "d2", "d3", "d4", "d5", "d6"},
                   {0}, {0}, {0}
                 };

  memset(ctx.cost, INTMAXVAL, sizeof(int) * OBST_MAX_ARR_LEN * OBST_MAX_ARR_LEN);

  find_obst(&ctx);

  print_obst(&ctx);
  return 0;
}
