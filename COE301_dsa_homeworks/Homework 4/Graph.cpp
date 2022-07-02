#include "Graph.h"

Graph::Graph(int n) {
   
   map<int,int> zero_map;
   zero_map[0] = 0;
   adjList.assign(n,zero_map);
   numVertices = n;
   numEdges = 0;

}

int Graph::getNumVertices() const {
   return numVertices;
}

int Graph::getNumEdges() const {
   return numEdges;
}

int Graph::getWeight(Edge e) const {
   return e.weight;
}

void Graph::add(Edge e) {
   
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[v].insert(make_pair(w, weight));
   adjList[w].insert(make_pair(v, weight));
   numEdges++;

}

void Graph::remove(Edge e) {
   
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[e.v].erase(w);
   adjList[e.w].erase(v);
   numEdges--;

}

map<int,int>::iterator Graph::findEdge(int v, int w) {
   
   map<int,int> m = adjList[v];
   map<int,int>::iterator iter = m.find(w);

   return iter;

}
