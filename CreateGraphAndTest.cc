#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"

using namespace std;

void printConnected(Graph g, string testQueryFile)
{
  fstream file;
  file.open(testQueryFile);
  string line;
  while (getline(file, line))
  {
    stringstream ss(line);
    string word;
    ss >> word;
    int fromVertex = stoi(word);
    ss >> word;
    int toVertex = stoi(word);
    // check connected
    cout << line << ": ";
    double weight = g.getEdgeWeight(fromVertex, toVertex);
    if (weight == -1)
    {
      cout << "not_connected" << endl;
    }
    else
    {
      cout << "connected " << weight << endl;
    }
  }
}

int graphTestDriver(int argc, char **argv)
{
  string graphFile = argv[1];
  string adjQueryFile = argv[2];
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  Graph graph = Graph::buildGraphFromFile(graphFile);
  // cout << "graph" << endl;
  // graph.printAdjList();
  // cout << "testing query" << endl;
  printConnected(graph, adjQueryFile);
  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>"
         << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
