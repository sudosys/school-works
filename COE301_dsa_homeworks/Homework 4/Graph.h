#include <vector>
#include <list>
#include <map>
#include "Edge.h"

using namespace std;

class Graph {
   
   public:
      int numVertices;
      int numEdges;

      vector<map<int, int>> adjList;

      Graph(int n);

      int getNumVertices() const;

      int getNumEdges() const;

      int getWeight(Edge e) const;

      void add(Edge e);

      void remove(Edge e);

      map<int,int>::iterator findEdge(int v, int w);

};