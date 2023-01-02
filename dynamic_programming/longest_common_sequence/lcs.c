#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define LCS_SEQ1_LEN 9
#define LCS_SEQ2_LEN 9

typedef enum lcs_direction
{
  LCS_DIRECTION_INVALID = 0,
  LCS_DIRECTION_EQUAL,
  LCS_DIRECTION_LEFT,
  LCS_DIRECTION_TOP
} lcs_direction;

void compute_lcs(int *seq1, int len1, int *seq2, int len2,
                 lcs_direction dir_matrix[][LCS_SEQ2_LEN], 
                 int val_matrix[][LCS_SEQ2_LEN])
{
  unsigned int i, j;

  /* Base condition: return when any of the sequences is 0 length */
  if (len1 == 0 || len2 == 0)
    return;

  /* Get indicies to compare */
  i = len1 - 1;
  j = len2 - 1;

  if (seq1[i] == seq2[j])
  {
    compute_lcs(seq1, len1 - 1, seq2, len2 - 1, dir_matrix, val_matrix);

    if (i == 0 || j == 0)
      val_matrix[i][j] = 1;
    else
      val_matrix[i][j] = val_matrix[i - 1][j - 1] + 1;

    dir_matrix[i][j] = LCS_DIRECTION_EQUAL;
  }
  else
  {
    int lcs_left = 0, lcs_top = 0;

    /* Explore the top branch */
    compute_lcs(seq1, len1 - 1, seq2, len2, dir_matrix, 
                val_matrix);

    /* Explore the left branch */
    compute_lcs(seq1, len1, seq2, len2 - 1, dir_matrix, 
                val_matrix);

    if (i != 0)
      lcs_top = val_matrix[i - 1][j];

    if (j != 0)
      lcs_left = val_matrix[i][j - 1];

    if (j != 0 && lcs_left > lcs_top)
    {
      dir_matrix[i][j] = LCS_DIRECTION_LEFT;
      val_matrix[i][j] = val_matrix[i][j - 1];
    }
    else if (i != 0)
    {
      dir_matrix[i][j] = LCS_DIRECTION_TOP;
      val_matrix[i][j] = val_matrix[i - 1][j];
    }
    else
      printf("bad_case\n");
  }
}

void print_lcs(int seq1[LCS_SEQ1_LEN], 
               lcs_direction dir_matrix[LCS_SEQ1_LEN][LCS_SEQ2_LEN],
               int val_matrix[LCS_SEQ1_LEN][LCS_SEQ2_LEN])
{
  int i, j;
  char dir;

  printf("val_matrix: \n");
  for (i = 0; i < LCS_SEQ1_LEN; i++)
  {
    for (j = 0; j < LCS_SEQ2_LEN; j++)
    {
      printf("%d ", val_matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("direction_matrix: \n");
  for (i = 0; i < LCS_SEQ1_LEN; i++)
  {
    for (j = 0; j < LCS_SEQ2_LEN; j++)
    {
      switch (dir_matrix[i][j])
      {
      case LCS_DIRECTION_EQUAL:
        dir = '\\';
        break;
      case LCS_DIRECTION_LEFT:
        dir = '-';
        break;
      case LCS_DIRECTION_TOP:
        dir = '|';
        break;
      case LCS_DIRECTION_INVALID:
        dir = 'a';
        break;
      default:
        dir = 'b';
        break;
      }
      printf("%c ", dir);
    }
    printf("\n");
  }
  printf("\n");

  printf("LCS: ");
  for (i = LCS_SEQ1_LEN - 1; i >= 0 ;)
  {
    for (j = LCS_SEQ2_LEN - 1; j >= 0;)
    {
      switch (dir_matrix[i][j])
      {
      case LCS_DIRECTION_EQUAL:
        printf("%d ", seq1[i]);
        i--;
        j--;
        break;
      case LCS_DIRECTION_LEFT:
        j--;
        break;
      case LCS_DIRECTION_TOP:
        i--;
        break;
      case LCS_DIRECTION_INVALID:
        goto exit;
      default:
        assert(0);
      }

      if (i < 0 || j < 0)
        goto exit;

      continue;
    }
  }
exit:
  printf("\n");
  return;
}

int main(void) 
{
  int seq1[LCS_SEQ1_LEN] = {10,22,9,33,21,50,41,60,80};
  int seq2[LCS_SEQ2_LEN] = {9,10,21,22,33,41,50,60,80};

  lcs_direction dir_matrix[LCS_SEQ1_LEN][LCS_SEQ2_LEN] = 
                                                  {LCS_DIRECTION_INVALID};
  int val_matrix[LCS_SEQ1_LEN][LCS_SEQ2_LEN] = {0};

  compute_lcs(seq1, LCS_SEQ1_LEN, seq2, LCS_SEQ2_LEN, dir_matrix, val_matrix);

  print_lcs(seq1, dir_matrix, val_matrix);

  return 0;
}

