

#include <fstream>
#include "Graph.h"
using namespace std;

Graph::Graph(){
   size = 0;
}

Graph::Graph(Graph& obj1){
   size = obj1.size;
   for (int i = 0; i < obj1.MAX_VERTICES; ++i){
      for (int j = 0; j < obj1.MAX_VERTICES ; ++j){
         T[i][j] = obj1.T[i][j];
      }
   }
   for(int v = 1; v < obj1.size; v++){
      vertices[v] = obj1.vertices[v];
   }
}

const Graph Graph::operator=(const Graph& right){
   if (this != &right) {
      size = right.size;
      for (int i = 0; i < right.MAX_VERTICES; ++i){
         for (int j = 0; j < right.MAX_VERTICES ; ++j){
            T[i][j] = right.T[i][j];
         }
      }
      for(int v = 1; v < right.size; v++){
         vertices[v] = right.vertices[v];
      }
   }
   return *this;
}

Graph:: ~Graph(){
   for(int v = 1; v < size; v++){
      EdgeNode *temp = vertices[v].edgeHead;
      while(temp != nullptr){
         delete temp;
         temp = temp->nextEdge;
      }
     delete vertices[v].data;
   }
}

   //-------------------------------- buildGraph ---------------------------------
   // Builds a graph by reading data from an ifstream
   // Preconditions:  infile has been successfully opened and the file contains
   //                 properly formated data (according to the program specs)
   // Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream& infile) {
   
   infile >> size;                          // data member stores array size
   if (infile.eof())
      return;
   infile.ignore();                         // throw away '\n' to go to next line
   
      // get descriptions of vertices
   for (int v = 1; v <= size; v++) {
      VertexNode node ;
      vertices[v] = node;
      infile >> node.data->v;      // read descriptions (use of this method is not mandatory)
                                   // store appropriately
   }
   
   
      // fill cost edge array
   int src = 1, dest = 1, weight = 1;
   for (;;) {
      infile >> src >> dest >> weight;
      if (src == 0 || infile.eof())
         break;
      insertEdge(src, dest, weight);
   }
}

   //For insertEdge, replace any previous edge that existed between the two vertices.
void Graph::insertEdge(int src, int dest, int weight){
   if(vertices[src].edgeHead == nullptr){
      vertices[src].edgeHead = new EdgeNode;
      vertices[src].edgeHead->adjVertex = dest;
      vertices[src].edgeHead->weight = weight;
      vertices[src].edgeHead->nextEdge = nullptr;
   }
   else{
      bool edgeExists = false;
      EdgeNode *curr = vertices[src].edgeHead;
      while(curr != nullptr){
         if(curr->adjVertex == dest){
            curr->weight = weight;
            edgeExists = true;
            break;
         }
         curr = curr->nextEdge;
      }
      if(!edgeExists){
         EdgeNode *e1 = new EdgeNode;
         e1->adjVertex = dest;
         e1->weight = weight;
         e1->nextEdge = nullptr;
         curr = vertices[src].edgeHead;
         while(curr->nextEdge != nullptr){
            curr = curr->nextEdge;
         }
         curr->nextEdge = e1;
      }
   }
   
}
void Graph::removeEdge(int src, int dest){
   if(vertices[src].edgeHead != nullptr){
      if(vertices[src].edgeHead->adjVertex == dest){
         EdgeNode *temp = vertices[src].edgeHead;
         vertices[src].edgeHead = vertices[src].edgeHead->nextEdge; //set edgeHead to the nextEdge
         delete temp;
      }
      EdgeNode *curr = vertices[src].edgeHead;
      while(curr->nextEdge != nullptr){
         if(curr->nextEdge->adjVertex==dest){
            EdgeNode *temp = curr->nextEdge;
            curr->nextEdge = curr->nextEdge->nextEdge;
            delete temp;
           // break;
         }
         curr = curr->nextEdge;
      }
   }
}
void Graph::findShortestPath(){
   
}

void Graph::display(int start, int end) const{
   
}
void Graph::displayAll() const{
   
}
