#include <vector>
#include <string>
#include <sstream>
#include "graph.h"
#include "binary_heap.h"

using namespace std;

class Node
{
public:
  int vertex;
  double cost;

  Node() {}

  Node(int _vertex, double _cost)
  {
    vertex = _vertex;
    cost = _cost;
  }

  bool operator<(const Node &otherNode) const
  {
    return cost < otherNode.cost;
  };
};

class Path
{
public:
  Path(int loneVertex)
  {
    noPath = true;
    path.push_back(loneVertex);
  }
  /**
   * _path should be in reverse order, from target being index 0 and source beind
   * last index;
   */
  Path(vector<int> _path, double _cost)
  {
    // cout << "received path length " << _path.size() << " with cost " << _cost << endl;
    path = _path;
    cost = _cost;
  }

  string summary()
  {
    if (noPath)
    {
      return to_string(path[0]) + ": not possible";
    }
    ostringstream pathStr;
    pathStr << path[0] << ": ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
      pathStr << to_string(path[i]) + " ";
    }
    pathStr << "cost: " << cost;
    return pathStr.str();
  }

private:
  bool noPath = false;
  vector<int> path;
  double cost;
};

class PathFinder
{
public:
  PathFinder(Graph g, int sourceVertex)
  {
    graph = g;
    source = sourceVertex;
    parentVertex = vector<int>(g.vertexCount());
    vertexMinCost = vector<double>(g.vertexCount());
    visited = vector<bool>(g.vertexCount());
    // SET MIN COST FOR ALL VERTEX TO INFO
    for (int vertex = 1; vertex <= g.vertexCount(); vertex++)
    {
      setVertexMinCost(vertex, numeric_limits<double>::max());
    }
    // RUN PATH FINDING ALGORITHM
    populatePathsFromSource();
  }

  Path getPathTo(int targetVertex)
  {
    double pathCost = getVertexMinCost(targetVertex);
    vector<int> path;
    if (pathCost == numeric_limits<double>::max())
    {
      Path p = {targetVertex};
      return p;
    }
    int current = targetVertex;
    if (targetVertex == source)
    {
      path.push_back(current);
      Path p(path, 0.0);
      return p;
    }

    while (current != source)
    {
      path.push_back(current);
      current = getVertexParent(current);
    }
    path.push_back(source);
    Path p = {path, pathCost};
    return p;
  }

private:
  Graph graph;
  int source;
  vector<int> parentVertex;
  vector<double> vertexMinCost;
  vector<bool> visited;
  BinaryHeap<Node> queue;

  void setVertexAsVisited(const int vertex)
  {
    visited[vertex - 1] = true;
  }

  bool hasVisitedVertex(int vertex)
  {
    return visited[vertex - 1];
  }

  void setVertexMinCost(int vertex, double newCost)
  {
    vertexMinCost[vertex - 1] = newCost;
  }

  double getVertexMinCost(int vertex)
  {
    return vertexMinCost[vertex - 1];
  }

  void setVertexParent(int vertex, int parent)
  {
    parentVertex[vertex - 1] = parent;
  }

  int getVertexParent(int child)
  {
    return parentVertex[child - 1];
  }

  void visitNode(Node &current)
  {
    setVertexAsVisited(current.vertex);
    for (DirectedEdge neighbor : graph.connectedEdges(current.vertex))
    {
      if (!hasVisitedVertex(neighbor.to))
      {
        double visitingCost = neighbor.weight + current.cost;
        if (visitingCost < getVertexMinCost(neighbor.to))
        {
          setVertexMinCost(neighbor.to, visitingCost);
          setVertexParent(neighbor.to, current.vertex);
          Node neighborNode = {neighbor.to, visitingCost};
          queue.insert(neighborNode);
        }
      }
    }
  }

  void populatePathsFromSource()
  {
    setVertexMinCost(source, 0);
    Node sourceNode = {source, 0};
    queue.insert(sourceNode);
    while (!queue.isEmpty())
    {
      Node current = queue.findMin();
      queue.deleteMin();
      visitNode(current);
    }
  }
};

void printAllPaths(PathFinder pf, int vertexCount)
{

  for (int i = 1; i <= vertexCount; i++)
  {
    cout << pf.getPathTo(i).summary() << endl;
  }
}

int pathfindDriver(int argc, char **argv)
{
  string graphFile = argv[1];
  int source = stoi(argv[2]);
  Graph graph = Graph::buildGraphFromFile(graphFile);
  PathFinder finder = {graph, source};
  printAllPaths(finder, graph.vertexCount());
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.

  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE>"
         << "<STARTING_VERTEX>" << endl;
    return 0;
  }

  pathfindDriver(argc, argv);

  return 0;
}
