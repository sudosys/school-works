#include <queue>
#include "Graph.h"

using namespace std;

class BFS {
 
 protected:
   const Graph &g;
   int count;
   vector<int> mark;
   vector<int> parents;

   void search(Edge e);

 public:
   BFS(const Graph &g);
		
   void startSearch();

};