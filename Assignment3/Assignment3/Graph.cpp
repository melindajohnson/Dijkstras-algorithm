/**---------------------------------------------------------------------------
 GRAPH.CPP
 Declaration of the Graph class
 Author: Melinda Stannah Stanley Jothiraj
 Student number- 1978413
 --------------------------------------------------------------------
 Graph class : Implements a Graph
 
 Struct EdgeNode : A EdgeNode  represents the edges that connect vertices in a graph
 - subscript of the adjacent vertex
 - weight of edge
 - Pointer to nextEdge
 
 Struct VertexNode : A VertexNode  represents the vertex in a graph
 - Pointer to the data in the Vertex
 - Pointer to the head of a  list of EdgeNodes
 
 Struct Table : A table  represents the information required for the Dijkstras algorithm
 - boolean visited flag
 - shortest known distance from source
 - previous vertex in path of min dist
 
 Includes additional features :
 -- The class contains the findShortestPath method to fill in the Table T with shortest path between vertices
 -- The class contains the buildGraph method that builds the Graph by reading  graph  data from a file
 -- The class contains the insertEdge method that builds the Graph by connecting vertices with direction and weight
 -- The class contains the removeedge method that removes edges from the Graph
 -- The class contains a copy constructor and an overloaded assignment operator which creates a deep copy of a Graph object
 -- The class contains the displayall method to display the Table T with its contents on shortest Path and weight to reach to the destination Vertex
 -- The class contains the display method to display the shortest Path and weight to reach to the destination Vertex for a particular source and destination vertex
 
 Assumptions :
 --That the input is properly formatted
 --The graph will have no more than 100 vertices.
 --------------------------------------------------------------------------------------------------------------------
 **/


#include "Graph.h"
using namespace std;
typedef pair<int, int> pi;

/**
 //-------------------------- Default constructor for class Graph ------------------------------------//
 Preconditions: None
 Postconditions: All private data member are initialised
 */
Graph::Graph(){
   size = 0;
}

/**
 //-------------------------- Copy constructor for class Graph ------------------------------------//
 Preconditions: A graph object obj1 is created
 Postconditions: The graph objects contains a deep copy of the content of obj1
 */
Graph::Graph(Graph& obj1){
   copyHelper(obj1);
}
/**
 //-------------------------- Overloaded assignment operator =  ------------------------------------//
 Preconditions: A graph object is created
 Postconditions: *this is assigned the same data as in the right object but at a different memory location
 @return graph object which is a deep copy of the object right
 */
const Graph Graph::operator=(const Graph& right){
   if (this != &right) {
      clear(*this);
      copyHelper(right);
   }
   return *this;
}

/**
 //-------------------------- Destructor  for class graph ------------------------------------//
 Preconditions:A graph object is created
 Postconditions: deallocate the elements stored in the Graph class
 */
Graph:: ~Graph(){
   for(int v = 1; v <= size; v++){
      delete vertices[v].data;
      EdgeNode *cur = vertices[v].edgeHead;
      while(cur != nullptr){
         EdgeNode *temp = cur->nextEdge;
         delete cur;
         cur = temp;
      }
     
   }
}

/**
 //-------------------------------- buildGraph ---------------------------------//
 Builds a graph by reading data from an ifstream
 Preconditions:  infile has been successfully opened and the file contains  properly formated data (according to the program specs)
 Postconditions: One graph is read from infile and stored in the object
 **/
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
/**
 //-------------------------- insertEdge ------------------------------------//
 Preconditions:A graph object is created and verices array is filled with vertex
 Postconditions: An edgeNode is created and added to the list of edge connected to edgeHead of is correponding vertexNode
 or replace any previous edge that existed between the two vertices by changing just the weight of the edgeNode
 */
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
/**
 //-------------------------- removeEdge ------------------------------------//
 Preconditions:A graph object is created with vertices and edgeNodes
 Postconditions: removes an edge whose adjVertex is equal to destination in the src vertex of the vertices array
 @return boolean true if successfully removed or false if edge doesnt exist
 */
bool Graph::removeEdge(int src, int dest){
   bool removed = false;
   if(vertices[src].edgeHead != nullptr){
      if(vertices[src].edgeHead->adjVertex == dest){
         EdgeNode *temp = vertices[src].edgeHead;
         vertices[src].edgeHead = vertices[src].edgeHead->nextEdge; //set edgeHead to the nextEdge
         delete temp;
         removed = true;
      }else{
         EdgeNode *curr = vertices[src].edgeHead->nextEdge; //set curr to the next Edge in the edges list
         EdgeNode *prev = vertices[src].edgeHead;
            //Traverse the edges list to find the edge and remove it if it exists
         while(curr != nullptr){
            if(curr->adjVertex==dest){
               EdgeNode *temp = curr;
               prev->nextEdge = curr->nextEdge;
               delete temp;
               removed = true;
               break;
            }
            else{
               prev = curr;
               curr = curr->nextEdge;
            }
         }
      }
   }
   return removed;
}

/**
 //-------------------------- findShortestPath ------------------------------------//
 method that computes all shortest paths
 Preconditions: A Graph object is created and the object is built with vertices and edges using the buildGraph method
 Postconditions: uses a priority queue to compute shortest path between all vertices and fills the contents in Table T[][]
 */
void Graph::findShortestPath(){
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
/**
 //-------------------------- displayAll ------------------------------------//
 Preconditions:A graph is created, built and shortest Paths have been computed
 Postconditions: Output a table formatted with description from to dist and path. path is obtained using recusive helper method findPath()
 */
void Graph::displayAll() const{
   std::cout << "Description           From  To   Dist  Path" <<endl;
   for(int i = 1; i <= size; i++){
      std::cout << vertices[i].data->getVertexData() << endl;
      for(int j = 1; j <= size; j++){
         if(i!=j){
            if(T[i][j].dist!=INT_MAX){
               std::cout << "                      "<< i << "     " << j << "     " << T[i][j].dist <<"    ";
               std::string path = " ";
               cout << findPath(i, j, path) << endl;
            }
            else
            {
               std::cout << "                      "<< i << "     " << j << "     --" ;
               std::cout << "     ";
               std::cout << endl;
            }
         }
      }
      std::cout << endl;
   }
}
/**
 //-------------------------- display ------------------------------------//
 Preconditions:A graph is created, built and shortest Paths have been computed
 Postconditions: Output description from to dist and path. path is obtained using recusive helper method findPath()
 */
void Graph::display(int start, int end) const{
   if(T[start][end].dist!=INT_MAX){
      std::cout <<start << "     " << end << "     " << T[start][end].dist<< "   ";
      std::string path = " ";
      cout << findPath(start, end, path) << endl;
      for(char& c : path) {
         int vertexNumber = c - '0' ;
         if(vertexNumber > 0){
            std::cout << vertices[vertexNumber].data->getVertexData();
         }
      }
      std::cout << endl;
   }
   else
   {
      std::cout <<start << "     " << end << "     " << "--" << endl<< "No Path Exitst" << endl;
   }
}
   //------------------------------------HELPER METHODS-------------------------------------------
/**
 //-------------------------- findPath ------------------------------------//
 Finds Path between source vertex and destination vertec using recursion
 Preconditions: Table T is filled with data for all vertices
 Postconditions: creates a string containing path from source to destination
 @return string containing path from source to destination
 */
std::string Graph::findPath(int src, int dest, std::string& path) const {
   if(src == dest) {
      path.insert(0,std::to_string(src));
      return path;
   }
   else
   {
      path.insert(0,std::to_string(dest));
      path.insert (0, 1, ' ');
      return findPath(src, T[src][dest].path, path);
      
   }
}

/**
 -------------------------- copyHelper ------------------------------------//
 Preconditions: A graph object obj1 is created
 Postconditions: Creates a deep copy of the Graph object
 */
void Graph::copyHelper(const Graph& obj1) {
   size = obj1.size;
      //Copy contents of the 2d array of Tables T[][]
   for (int i = 0; i < obj1.MAX_VERTICES; ++i){
      for (int j = 0; j < obj1.MAX_VERTICES ; ++j){
         T[i][j] = obj1.T[i][j];
      }
   }
      //Copy contents of the vertices array
   for(int v = 1; v <= obj1.size; v++){
         //Create deep copy of data in Vertex Node
      vertices[v].data = new Vertex;
      vertices[v].data->setVertexData(obj1.vertices[v].data->getVertexData());
         //Create deep copy of edgeHead and its list in Vertex Node
      if (obj1.vertices[v].edgeHead == nullptr) {
         vertices[v].edgeHead  = nullptr;
      }
      else {
         vertices[v].edgeHead  = new EdgeNode;
         vertices[v].edgeHead->adjVertex = obj1.vertices[v].edgeHead->adjVertex;
         vertices[v].edgeHead->weight = obj1.vertices[v].edgeHead->weight;
         EdgeNode *current = vertices[v].edgeHead;
         EdgeNode *currentObj = obj1.vertices[v].edgeHead->nextEdge;
         while (currentObj != nullptr) {
            EdgeNode *newEdge = new EdgeNode;
            newEdge->adjVertex = currentObj->adjVertex;
            newEdge->weight = currentObj->weight;
            current->nextEdge = newEdge;
            current = current->nextEdge;
            currentObj = currentObj->nextEdge;
         }
      }
   }
}
/**
 -------------------------- clear ------------------------------------//
 Preconditions: A graph object obj1 is created
 Postconditions: All dynamically allocated objects are deallocated and memory is freed
 */
void Graph::clear(const Graph& obj1){
   for(int v = 1; v <= size; v++){
      delete vertices[v].data;
      EdgeNode *cur = vertices[v].edgeHead;
      while(cur != nullptr){
         EdgeNode *temp = cur->nextEdge;
         delete cur;
         cur = temp;
      }
   }
   for (int i = 0; i < obj1.MAX_VERTICES; ++i){
      for (int j = 0; j < obj1.MAX_VERTICES ; ++j){
         T[i][j].dist = INT_MAX;
         T[i][j].path = 0;
         T[i][j].visited = false;
      }
   }
}
