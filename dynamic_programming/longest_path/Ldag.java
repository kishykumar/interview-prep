import java.util.ArrayList; 
import java.util.List; 
import java.util.Map;
import java.util.LinkedHashMap;
import java.util.HashMap;
import java.util.Set;

class Vertex
{
  int  value;

  Vertex(int value)
  {
    this.value = value;
  }

  @Override
  public boolean equals(Object obj)
  {
    if (!(obj instanceof Vertex))
      return false;

    Vertex v = (Vertex)obj;
    if (v == this)
      return true;

    return (this.value == v.value);
  }

  @Override
  public int hashCode()
  {
    return this.value;
  }

  public String toString()
  {
    return String.valueOf(this.value);
  }
}

class Graph
{
  /* Adjacency list */
  Map<Vertex, ArrayList<Vertex>> vertices = new LinkedHashMap<Vertex, ArrayList<Vertex>>();

  /* Matrix to stash longest path lengths */

  Graph()
  {
  }

  void addVertex(int value)
  {
    Vertex v = new Vertex(value);
    this.vertices.put(v, new ArrayList<Vertex>());
  }

  void addEdge(int val_v1, int val_v2)
  {
    Vertex v1 = new Vertex(val_v1);
    Vertex v2 = new Vertex(val_v2);

    this.vertices.get(v1).add(v2);
  }

  public String toString()
  {
    return this.vertices.toString();
  }

  public int longestPath(int val_v1, int val_v2, int[][] longestPathMatrix)
  {
    Vertex              v1 = new Vertex(val_v1);
    Vertex              v2 = new Vertex(val_v2);
    ArrayList<Vertex>   edgeList = this.vertices.get(v1);
    int                 lp = 0;
    int                 maxLongestPath = -1;
    Set<Vertex>         keys = this.vertices.keySet();
    List<Vertex>        listKeys = new ArrayList<Vertex>(keys);
    int                 indexV1 = listKeys.indexOf(v1);
    int                 indexV2 = listKeys.indexOf(v2);

    if (longestPathMatrix[indexV1][indexV2] != 0)
      return longestPathMatrix[indexV1][indexV2];

    if (edgeList == null || edgeList.size() == 0)
      return 0;

    for (Vertex v: edgeList)
    {
      lp = longestPath(v.value, val_v2, longestPathMatrix);

      if ((lp != 0 || (v.value == val_v2)) && lp > maxLongestPath)
        maxLongestPath = lp;
    }

    System.out.println("Longest path between: " + val_v1 + " and " + val_v2 + " is: " + (maxLongestPath + 1));

    longestPathMatrix[indexV1][indexV2] = (maxLongestPath + 1);
    return (maxLongestPath + 1);
  }
}

public class Ldag
{
  // Driver code 
  public static void main(String[] args) 
  {
    /* Initialize a graph with 6 verticies */
    Graph    gr = new Graph();
    int[][]  longestPathMatrix = new int[5][5];

    gr.addVertex(1);
    gr.addVertex(2);
    gr.addVertex(3);
    gr.addVertex(4);
    gr.addVertex(5);

    gr.addEdge(1, 2);
    gr.addEdge(1, 3);
    gr.addEdge(3, 2);
    gr.addEdge(2, 4);
    gr.addEdge(3, 4);

    System.out.println("Input graph: ");
    System.out.println(gr);

    System.out.println("Longest path: " + gr.longestPath(1, 6, longestPathMatrix));
  }
}
