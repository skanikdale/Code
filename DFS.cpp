#include "stdafx.h"
#include <iostream>
#include <list>

/*
      Depth first search Algorithm


   start->  1
         2    5
       3   4    8
      6          9
     7


   */

using namespace std;

class Graph2
{
  int v;                // No. of vertices
  list<int> * adj;      // Pointer to array containing adjacency list  *** Doubly linked list ****

public:
  Graph2(int v);
  void addEdge(int v, int w); // function to add an edge to Graph2
  void DFSPrint(int node);            // prints DFS from root s
};


Graph2::Graph2(int v)
{
  this->v = v;
  adj = new list<int>[v];
}

void Graph2::addEdge(int v, int w)
{
  adj[v].push_back(w);  // add edge to vertix's list
}

void Graph2::DFSPrint(int node)
{
  bool* visited = new bool[v];

  for(int i = 1; i <= v; i++)
    visited[i] = false;

  visited[node] = true;
  cout << node << " ";

  list<int>::iterator itr;

  for(itr = adj[node].begin(); itr != adj[node].end(); ++itr)
  {
    if(!visited[*itr])
      DFSPrint(*itr);
  }
}

/*
   start->  1
         2    5
       3   4    8
      6          9
     7
*/

void testDFS()
{
    // Create a Graph2 with 9 vertices
    Graph2 g(9);

    // Create edges in Graph2
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 6);
    g.addEdge(6, 7);
    g.addEdge(5, 8);
    g.addEdge(8, 9);
 
    cout << "Following is Depth First Traversal (starting from vertex 1) \n";
    g.DFSPrint(1);
 
    return;
}