class Edge {

   public:
      
      int v, w, weight;
      Edge(int firstVertex, int secondVertex, int edgeWeight) {
         v = firstVertex;
         w = secondVertex;
         weight = edgeWeight; 
      }

};