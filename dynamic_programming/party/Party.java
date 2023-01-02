// TODO: Introduce a HashMap with key-value pairs of String->friendliness
import java.util.Map;
import java.util.HashMap;
// Insert: friendMap.put("string");
// Check:
// Delete:
// 


class Guest
{
  private int     friendliness;
  private Guest   employee;
  private Guest   peer;

  public Guest(int friend, Guest emp, Guest pe)
  {
    this.friendliness = friend;
    this.employee = emp;
    this.peer = pe;
  }

  public int getFriendliness() { return this.friendliness; }
  public Guest getEmployee() { return this.employee; }
  public Guest getPeer() { return this.peer; }

  public void setFriendliness(int friend) { this.friendliness = friend; }
  public void setEmployee(Guest emp) { this.employee = emp; }
  public void setPeer(Guest pe) { this.peer = pe; }
}

public class Party
{
  private static Map<String, Integer> friendMap = new HashMap<String, Integer>();
  // getMaxFriendliness(parent) = max ( getMaxFriendliness(all children) OR (parent.friendliness + sum of all grandchildren) )

  private static int max(int m1, int m2)
  {
    return (m1 > m2) ? m1 : m2;
  }

  private static int getMaxFriendliness(Guest guest)
  {
    Guest child, grandChild;
    int childrenFriendliness = 0;
    int grandChildrenFriendliness = 0;
    int parentFriendliness = 0;

    // Iterate over children
    child = guest.getEmployee();
    while (child != null)
    {
      childrenFriendliness += getMaxFriendliness(child);

      // Iterate over grand children
      grandChild = child.getEmployee();
      while (grandChild != null)
      {
        grandChildrenFriendliness += getMaxFriendliness(grandChild);
        grandChild = grandChild.getPeer();
      }

      child = child.getPeer();
    }

    parentFriendliness = max(childrenFriendliness, guest.getFriendliness() + grandChildrenFriendliness);
    return parentFriendliness;
  }

  public static void main(String[] args)
  {
    int maxFriendliness = 0;
    Guest engr3 = new Guest(10, null, null);
    Guest engr2 = new Guest(10, null, engr3);
    Guest engr1 = new Guest(10, null, engr2);

    Guest svp4 = new Guest(80, null, null);
    Guest svp3 = new Guest(80, null, svp4);
    Guest svp2 = new Guest(80, null, null);
    Guest svp1 = new Guest(80, null, svp2);

    Guest evp2 = new Guest(900, svp3, null);
    Guest evp1 = new Guest(90, svp1, evp2);
    Guest president = new Guest(100, evp1, null);

    maxFriendliness = getMaxFriendliness(president);

    System.out.println("Max friendliness is: " + maxFriendliness);
  }
}
