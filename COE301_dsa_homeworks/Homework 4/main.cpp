#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Graph.h"

Graph* randomGraphGenerator(int numOfVertices, float probability) {

    Graph* graph = new Graph(numOfVertices);
    std::map<int,int>::iterator mapIterator;
    int chance;
    int edgeWeight;

    for (int i = 0; i < graph->getNumVertices(); i++) {        

        mapIterator = graph->adjList.at(i).begin();

        chance = rand() % 100 + 1;
        edgeWeight = rand() % 10 + 1;

        if (chance <= probability*100) {
            Edge newEdge(i, mapIterator->first, edgeWeight);
            graph->add(newEdge);
        }

    }

    return graph;

}

void DFS(Graph* graph, int currentVertex, bool visitedVertices[]) {

    visitedVertices[currentVertex] = true;

    std::map<int, int>::iterator iter;
    int iter_count = 0;

    for (iter = graph->adjList.at(currentVertex).begin(); iter != graph->adjList.at(currentVertex).end(); iter++) {

        if(!visitedVertices[iter_count]) { DFS(graph, iter_count, visitedVertices); }

        iter_count++;

    }

}

int findNumComponents(Graph* graph) {

    bool* visitedVertices = new bool[graph->getNumVertices()];

    int componentCount = 0;

    for (int vertexCounter = 0; vertexCounter < graph->getNumVertices(); vertexCounter++) {
        visitedVertices[vertexCounter] = false;
    }

    for (int vertexCounter = 0; vertexCounter < graph->getNumVertices(); vertexCounter++) {

        if (!visitedVertices[vertexCounter]) {
            DFS(graph, vertexCounter, visitedVertices);
            componentCount++;
        }

    }

    return componentCount;

}

int main() {

    srand(time(NULL));

    Graph* graph = randomGraphGenerator(10000, 0);

    // std::cout << graph->getNumVertices() << std::endl;
    // std::cout << graph->getNumEdges() << std::endl;

    Graph* g = new Graph(6);
    // std::cout << g.getNumVertices() << std::endl;
    Edge e(1,0,1);
    Edge x(2,3,1);
    Edge y(4,5,1);
    g->add(e);
    g->add(x);
    g->add(y);
    // std::cout << g.getNumEdges() << std::endl;
    
    std::cout << findNumComponents(g) << std::endl;

    return 0;

}
