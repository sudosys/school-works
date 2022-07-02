#include "BFS.h"

BFS::BFS(const Graph &g) : g(g), mark(g.getNumVertices(), -1),
                      parents(g.getNumVertices(), 0), count(0) {
   startSearch();
}

void BFS::startSearch() {
   for (int v = 0; v < g.getNumVertices(); v++)
      if (mark[v] == -1)
         search(Edge(v,v, 0));
}

void BFS::search(Edge e) {
   
   queue<Edge> q;

   map<int, int> m;
   map<int, int>::iterator iter;

   q.push(e);

   while (!q.empty()) {

      e = q.front();

      q.pop();

      if (mark[e.w] == -1) { 

         int v = e.v,
             w = e.w,
             weight = e.weight;
         mark[w] = count++;
         parents[w] = v;

         m = g.adjList[w];
         for (iter = m.begin(); iter != m.end(); iter++) 
            if (mark[iter->first] == -1) 
               q.push(Edge(w, iter->first, iter->second));

      }
   }
}