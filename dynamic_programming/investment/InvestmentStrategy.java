// Given initial amount 10,000 dollars
// Given a matrix of N investments and 10 years
// Fees for changing investments f2 > f1

public class InvestmentStrategy
{
  public static final int TOTAL_YEARS = 5;
  public static final int TOTAL_INVESTMENTS = 5;
  public static final int INITIAL_INVESTMENT = 100; // dollars
  public static final int INVESTMENT_CHANGE_FEES = 50; // dollars
  public static final int INVESTMENT_RENEWAL_FEES = 20; // dollars

  private static void printMatrices()
  {
    System.out.println("Money Matrix: ");
    for (int i = 0; i < TOTAL_YEARS; i++)
    {
      for (int j = 0; j < TOTAL_INVESTMENTS; j++)
        System.out.print(moneyMatrix[i][j] + " ");
      System.out.println();
    }

    System.out.println("\nInvestment Matrix: ");
    for (int i = 0; i < TOTAL_YEARS; i++)
    {
      for (int j = 0; j < TOTAL_INVESTMENTS; j++)
        System.out.print(investmentMatrix[i][j] + " ");
      System.out.println();
    }
  }

  private static int bestInvestmentStrategy()
  {
    int year, investmentNum, investment_j;
    int moneyMax, temp;

    // data structures:
    // 1. investmentMatrix - 2D array of the N-1th year investment that was picked
    // 2. moneyMatrix - 2D array of the most money that can be grown using this investment cell and the series before it shown in the investmentMatrix.

    // Optimal Max money in a year x = max ( i=1-N max money from ith investment in that year x )
    // max money from ith investment in year x i.e. money[i][x] = max ( j=1-N money[j][x-1] * growth[i][x] - fees{f1 or f2} )

    // optimal substructure: 
    // money[i][x] exhibits optimal substructure property

    // overlapping subproblems: 
    // for different values of i in money[i][x], we will end up re-using money[j][x-1]

    // 1. loop over the number of years
    // 2. calcuate the money you can make from all N investments if picked in that year by looking at both moneyMatrix and investmentMatrix
    //    money[investmentNum][year] = max ( growthMatrix[investmentNum][year] * money[investmentNum][year - 1] - INVESTMENT_RENEWAL_FEES, // same investment
    //                                     iterate over all other investments ->  growthMatrix[investmentNum][year] * money[other_investmentNum][year - 1] - INVESTMENT_CHANGE_FEES

    for (year = 0; year < TOTAL_YEARS; year++)
    {
      for (investmentNum = 0; investmentNum < TOTAL_INVESTMENTS; investmentNum++)
      {
        if (year == 0)
        {
          moneyMatrix[investmentNum][year] = INITIAL_INVESTMENT * growthMatrix[investmentNum][year];
          continue;
        }

        moneyMax = 0;
        investment_j = 0;

        for (int j = 0; j < TOTAL_INVESTMENTS; j++)
        {
          temp = (moneyMatrix[j][year - 1] * growthMatrix[investmentNum][year]);
          temp -= ((investmentNum != j) ? INVESTMENT_CHANGE_FEES : INVESTMENT_RENEWAL_FEES);

          if (temp > moneyMax)
          {
            moneyMax = temp;
            investment_j = j;
          }
        }

        moneyMatrix[investmentNum][year] = moneyMax;
        investmentMatrix[investmentNum][year] = investment_j;
      }
   }

    int optimalMoney = Integer.MIN_VALUE;
    for (int i = 0; i < TOTAL_INVESTMENTS; i++)
    {
      if (optimalMoney < moneyMatrix[i][TOTAL_YEARS - 1])
        optimalMoney = moneyMatrix[i][TOTAL_YEARS - 1];
    }

    return optimalMoney;
  }

  public static final int[][] growthMatrix = {
                                               {1, 5, 1, 5, 1},
                                               {2, 4, 2, 4, 2},
                                               {3, 3, 3, 3, 3},
                                               {4, 2, 4, 2, 4},
                                               {5, 1, 5, 1, 5}
                                             }; // growth factor

  public static int moneyMatrix[][] = new int[5][5]; // initialized to 0
  public static int investmentMatrix[][] = new int[5][5]; // initialized to 0

  public static void main(String[] args)
  {
    printMatrices();
    System.out.println("optimal_money " + bestInvestmentStrategy());
    printMatrices();
  }
}
