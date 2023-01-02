#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INTMAXVAL ((1 << 31) - 1)
#define TRUE  (1)
#define FALSE (0)

void build_pi_table(char *pattern, int pattern_len, int *pi_table)
{
  int i, k = 1;

  printf("%d pi_table is: ", pattern_len);
  pi_table[0] = 0;
  for (i = 1; i < (pattern_len + 1); i++)
  {
    if (pattern[i - 1] == pattern[k - 1] && i != k)
    {
      pi_table[i] = k;
      k++;
    }
    else
    {
      pi_table[i] = 0;
      k = 1;
    }

    printf("%d ", pi_table[i]);
  }
  printf("\n");
}

int find_pattern(char *string, int string_len, char *pattern, int pattern_len)
{
  int       pattern_idx = INTMAXVAL;
  int       i, j;
  int      *pi_table;
  int       matchFound;
  int       exit = FALSE;

  pi_table = (int *)malloc((pattern_len + 1) * sizeof(int));
  /* malloc failed, return pattern not found. Ideally, should signal 
   * exception.
   */
  if (pi_table == NULL)
    return INTMAXVAL;

  build_pi_table(pattern, pattern_len, pi_table);

  j = 0;
  for (i = 0; i < string_len && !exit; i++)
  {
    matchFound = FALSE;
    do
    {
      if (string[i] == pattern[j])
      {
        /* Initialize the beginning of the substring match */
        if (j == 0)
          pattern_idx = i;

        printf("match found %c %c\n", string[i], pattern[j]);
        matchFound = TRUE;
        j++;

        if (j == pattern_len)
        {
          exit = TRUE;
          break;
        }
      }
      else
      {
        printf("match not found %c %c\n", string[i], pattern[j]);

        j = pi_table[j];

        /* Clear the pattern match index on mismatch */
        if (j == 0)
          pattern_idx = INTMAXVAL;
        else
          pattern_idx = i - j;
      }
    }
    while (j != 0 && matchFound == FALSE);
  }

  free(pi_table);
  return pattern_idx;
}

int main()
{
  char   *string = "acabcabcabababd";
  char   *pattern = "";
  int     pattern_idx;

  pattern_idx = find_pattern(string, strlen(string), pattern, strlen(pattern));
  printf("index is: %d\n", pattern_idx);
}
