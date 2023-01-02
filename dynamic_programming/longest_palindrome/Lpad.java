import java.util.ArrayList;

public class Lpad
{
  static int findLongestPalindrome(String input, int startIdx, 
                                   int endIdx, int[] palindroneArr)
  {
    int longestPalindromeLen;

    /* Pseudo code 
     * 1. Two pointers: i points to beginning of string and j at the end.
     *    Compare the char at i and j.
     * 2. If a[i] == a[j], solve subproblem 
     *    findLongestPalindrome(i + 1, j - 1).
     * 3. a[i] != a[j], solve 2 subproblems 
     *    findLongestPalindrome(i + 1, j), (i, j - 1).
     */

    /* Base condition */
    if (startIdx == endIdx)
    {
      //palindroneArr[startIdx] = 1;

      System.out.println("B startIdx: " + startIdx + 
                         " charAt-startIdx: " + input.charAt(startIdx) +
                         " endIdx: " + endIdx);

      return 1;
    }

    if (input.charAt(startIdx) == input.charAt(endIdx))
    {
      longestPalindromeLen = findLongestPalindrome(input, startIdx + 1,
                                                   endIdx - 1, palindroneArr);
      longestPalindromeLen += 2;

      palindroneArr[startIdx] = 1;
      palindroneArr[endIdx] = 1;
      System.out.println("NB startIdx: " + startIdx + 
                         " charAt-startIdx: " + input.charAt(startIdx) +
                         " endIdx: " + endIdx + 
                         " longestPalindromeLen: " + longestPalindromeLen);
    }
    else
    {
      int longestPalindromeLenLeft, longestPalindromeLenRight;

      longestPalindromeLenRight = findLongestPalindrome(input, startIdx + 1, 
                                                        endIdx, palindroneArr);

      longestPalindromeLenLeft = findLongestPalindrome(input, startIdx, 
                                                       endIdx - 1, palindroneArr);

      longestPalindromeLen = 
        (longestPalindromeLenRight > longestPalindromeLenLeft) ? 
         longestPalindromeLenRight : 
         longestPalindromeLenLeft;
        
    }

    return longestPalindromeLen;
  }

  public static void main(String[] args)
  {
    String    input = "character";
    int[]     palindroneArr = new int[input.length()]; /* Initialized to 0 */
    int       i = 0;

    System.out.println("LP: " + findLongestPalindrome(input, 0, 
                       input.length() - 1, palindroneArr));

    for (i = 0; i < palindroneArr.length; i++)
    {
      if (palindroneArr[i] == 1)
        System.out.printf("%c", input.charAt(i));
    }
    System.out.println();
  }
}
