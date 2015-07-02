#include "stdafx.h"
#include <iostream>
#include <list>

/*
      Breadhth first search Algorithm


            0 ---------->  1
            ^             /
            |           /
            |        /
            |      /    
            |   /
              /
   start->  2 -----------> 3


   */

using namespace std;

class Graph
{
  int v;                // No. of vertices
  list<int> * adj;      // Pointer to array containing adjacency list  *** Doubly linked list ****

public:
  Graph(int v);
  void addEdge(int v, int w); // function to add an edge to graph
  void BFSPrint(int s);       // prints BFS from root s
};


Graph::Graph(int v)
{
  this->v = v;
  adj = new list<int>[v];
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w);  // add edge to vertix's list
}

void Graph::BFSPrint(int s)
{
  // First mark all the vertices as not visited
  bool* visited = new bool[v];

  for(int i = 0; i < v; i++)
    visited[i] = false;

  // Create a queue for BFS
  list<int> queue;

  // Mark the current node as visited & add it to queue
  visited[s] = true;
  queue.push_back(s);

  // 'itr' will be used to get all adjacent vertices of a vertex
  list<int>::iterator itr;

  while(!queue.empty())
  {
    // Dequeue vertex from queue & print it
    s = queue.front();
    cout << s << " ";
    queue.pop_front();

    // Get all adjacent vertices of the dequeueed vertex s
    // If a adjacent has not been visited, then mark it visited
    // and enque it
    for(itr = adj[s].begin(); itr != adj[s].end(); ++itr)
    {
      if(!visited[*itr])
      {
        visited[*itr] = true;
        queue.push_back(*itr);
      }
    }
  }
}

void testBFS()
{
    // Create a graph with 4 vertices
    Graph g(4);

    // Create edges in graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
    g.BFSPrint(2);
 
    return;
}