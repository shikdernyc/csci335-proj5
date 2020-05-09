#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outsode those statements

using namespace std;

struct DirectedEdge
{
  int to;
  int from;
  double weight;
};
// =================== MAIN CLASS ===================

class Graph
{
public:
  Graph()
  {
  }

  Graph(int numOfVertex)
  {
    setVertexCount(numOfVertex);
  }

  void addEdge(int from, int to, double weight)
  {
    DirectedEdge de;
    de.to = to;
    de.from = from;
    de.weight = weight;
    connectedEdges(from).push_back(de);
  }

  void setVertexCount(int vertexCount)
  {
    adjList = vector<vector<DirectedEdge>>(vertexCount);
  }

  // =============== HELPER METHODS ===============

  int vertexCount()
  {
    return adjList.size();
  }

  vector<DirectedEdge> &connectedEdges(int vertex)
  {
    return adjList.at(vertex - 1);
  }

  static Graph buildGraphFromFile(string graphFile)
  {
    fstream file;
    file.open(graphFile);
    string line;

    getline(file, line);
    int vertexCount = stoi(line);
    Graph g(vertexCount);
    while (getline(file, line))
    {
      stringstream ss(line);
      string currentWord;
      ss >> currentWord;
      int fromVertex = stoi(currentWord);
      // cout << fromVertex << endl;
      while (ss >> currentWord)
      {
        int toVertex = stoi(currentWord);
        ss >> currentWord;
        double weight = stod(currentWord);
        // cout << "\t" << toVertex << ": " << weight << endl;
        g.addEdge(fromVertex, toVertex, weight);
      }
    }

    file.close();
    return g;
  }

  /**
   *  Receives costs between directly connected vertexes
   *  @returns {int} weight between edge. Returns -1 if not DIRECTLY connected
   */
  double getEdgeWeight(int fromVertex, int toVertex)
  {
    for (DirectedEdge de : connectedEdges(fromVertex))
    {
      if (de.to == toVertex)
      {
        return de.weight;
      }
    }
    return -1;
  }

  // DEVELOPMENT PURPOSES
  void printAdjList()
  {
    for (int fromV = 1; fromV <= vertexCount(); fromV++)
    {
      cout << fromV << "--> ";
      for (DirectedEdge toV : connectedEdges(fromV))
      {
        cout << toV.to << " ";
      }
      cout << endl;
    }
  }

private:
  vector<vector<DirectedEdge>> &getAdjList()
  {
    return adjList;
  }
  vector<vector<DirectedEdge>> adjList; // 0 based. refence v1 at adjList[0]
};

#endif
