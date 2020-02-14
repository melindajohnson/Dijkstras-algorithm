

#include <fstream>
#include <iostream>
#include <queue>
#include "Graph.h"
using namespace std;
typedef pair<int, int> pi;
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
   for(int v = 1; v <= obj1.size; v++){
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
      for(int v = 1; v <= right.size; v++){
         vertices[v] = right.vertices[v];
      }
   }
   return *this;
}

Graph:: ~Graph(){
   for(int v = 1; v <= size; v++){
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
   infile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // throw away '\n' to go to next line
   
      // get descriptions of vertices
   for (int v = 1; v <= size; v++) {
      std::string name;
      getline(infile, name);
      Vertex *v1 = new Vertex();
      v1->setVertexData(name);
      vertices[v].data = v1;
   }
   
      // fill cost edge array
   int src = 1, dest = 1, weight = 1;
   for (;;)
   {
      infile >> src >> dest >> weight;
      if (src == 0 || infile.eof()) break;
      insertEdge(src, dest, weight);
   }
   
}

   //For insertEdge, replace any previous edge that existed between the two vertices.
void Graph::insertEdge(int src, int dest, int weight){
   EdgeNode *e1 = new EdgeNode;
   if(vertices[src].edgeHead == nullptr){
      vertices[src].edgeHead = e1;
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
      //   for(int i = 1; i <= size; i++){
      //      for(int j = 1; j <= size; j++){
      //         if(i==j) {
      //            T[i][j].dist = 0;
      //         }
      //      }
      //      int count = 1;
      //      while(count < size)
      //      {
      //         int vertexToBeVisited = MinDistVertex(i);
      //         EdgeNode *curr = vertices[vertexToBeVisited].edgeHead;
      //         while(curr != nullptr)
      //         {
      //            int currentDistance = T[i][vertexToBeVisited].dist + curr->weight;
      //            if(T[i][curr->adjVertex].dist > currentDistance)
      //            {
      //               T[i][curr->adjVertex].dist = currentDistance;
      //               T[i][curr->adjVertex].path = vertexToBeVisited;
      //            }
      //            //
      //            curr = curr->nextEdge;
      //         }
      //         T[i][vertexToBeVisited].visited = true;
      //         count++;
      //      }
      //   }
   for(int i = 1; i <= size; i++){
     
      priority_queue<pi, vector<pi>, greater<pi> > queue1;
        // Initialisation
      T[i][i].dist = 0;
      int count = 1;
      queue1.push(make_pair(0, i));
      while(!queue1.empty() && count < size )
      {
         int vertexToBeVisited = queue1.top().second;
         T[i][vertexToBeVisited].visited = true;
         queue1.pop();
            //visit all of the adjacent vertices of the current vertex.
         EdgeNode *curr = vertices[vertexToBeVisited].edgeHead;
         while(curr != nullptr)
         {
            int currentDistance = T[i][vertexToBeVisited].dist + curr->weight;
            if(T[i][curr->adjVertex].dist > currentDistance)
            {
               T[i][curr->adjVertex].dist = currentDistance;
               T[i][curr->adjVertex].path = vertexToBeVisited;
               queue1.push(make_pair(currentDistance, curr->adjVertex));
            }
            curr = curr->nextEdge;
         }
         count++;
      }
   }
}


   //int Graph::MinDistVertex(int src){
   //   int minDistance = INT_MAX;
   //   int index = 0;
   //   for(int i = 1; i <= size; i++){
   //      if(T[src][i].visited == false ){
   //         if(T[src][i].dist < minDistance){
   //            minDistance = T[src][i].dist;
   //            index = i;
   //         }
   //      }
   //   }
   //   return index;
   //}

void Graph::displayAll() const{
   std::cout << "Description             From  To   Dist  Path" <<endl;
   for(int i = 1; i <= size; i++){
      std::cout << vertices[i].data->getVertexData() << endl;
      for(int j = 1; j <= size; j++){
         if(i!=j){
            if(T[i][j].dist!=INT_MAX){
               std::cout << "                        "<< i << "     " << j << "     " << T[i][j].dist <<"   ";
               std::vector<int> path;
               printPath(i, j, path);
               for (auto it = path.crbegin(); it != path.crend(); it++)
               {
                  std::cout << *it << ' ';
               }
               std::cout << endl;
            }
            else
            {
               std::cout << "                        "<< i << "     " << j << "     --" ;
               std::cout << "     ";
               std::cout << endl;
            }
         }
      }
      std::cout << endl;
   }
}

std::vector<int> Graph::printPath(int src, int dest, std::vector<int>& path) const {
   if(src == dest) {
      path.push_back(src);
      return path;
   }
   else
   {
      path.push_back(dest);
      return printPath(src, T[src][dest].path, path);
   }
}

void Graph::printPathDescription(int src, int dest) const {
   if(src == dest) {
      std::cout << vertices[src].data->getVertexData();
   }
   else
   {
      printPathDescription(src, T[src][dest].path);
      std::cout << vertices[dest].data->getVertexData();
   }
}

void Graph::display(int start, int end) const{
   std::cout <<start << "     " << end << "     " << T[start][end].dist<< "   ";
   std::vector<int> path;
   printPath(start, end, path);
   for (auto it = path.crbegin(); it != path.crend(); it++)
   {
      std::cout << *it << ' ';
   }
   std::cout << endl;
   for (auto it = path.crbegin(); it != path.crend(); it++)
   {
      int vertexNumber = *it;
      std::cout << vertices[vertexNumber].data->getVertexData();
      
   }
}

