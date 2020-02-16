/**---------------------------------------------------------------------------
 GRAPH.H
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
#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <climits>
#include "Vertex.h"

class Graph {

private:
   static const int MAX_VERTICES = 5;
   
   struct EdgeNode {
      int adjVertex;                   // subscript of the adjacent vertex
      int weight;                      // weight of edge
      EdgeNode *nextEdge = nullptr;    // pointer to next EdgeNode
   };
   
   struct VertexNode {
      EdgeNode *edgeHead = nullptr;    // head of the list of edges
      Vertex *data;                   // store vertex data here
   };
   
   // table of information for Dijkstra's algorithm
   struct Table {
      bool visited = false ;            // whether vertex has been visited
      int dist = INT_MAX;               // shortest known distance from source
      int path = 0;                     // previous vertex in path of min dist
   };
   
   VertexNode vertices[MAX_VERTICES];   // array of VertexNodes
   int size = 0;                        // number of vertices in the graph
   Table T[MAX_VERTICES][MAX_VERTICES]; // stores visited, distance, path in order to solve for all sources
   
   /**
    //-------------------------- findPath for class Graph ------------------------------------//
    Finds Path between source vertex and destination vertec using recursion
    Preconditions: Table T is filled with data for all vertices
    Postconditions: creates a string containing path from source to destination
    @return string containing path from source to destination
    */
   std::string findPath(int src, int dest, std::string& path)const;
   
   /**
    -------------------------- copyHelper ------------------------------------//
    Preconditions: A graph object obj1 is created
    Postconditions: Creates a deep copy of the Graph object
    */
   void copyHelper(const Graph& obj1);
   
   /**
    -------------------------- clear ------------------------------------//
    Preconditions: A graph object obj1 is created
    Postconditions: All dynamically allocated objects are deallocated and memory is freed
    */
   void clear(const Graph& obj1);
   
   
public:
   /**
    //-------------------------- Default constructor for class Graph ------------------------------------//
    Preconditions: None
    Postconditions: All private data member are initialised
    */
   Graph();
   /**
    //-------------------------- Copy constructor for class Graph ------------------------------------//
    Preconditions: A graph object obj1 is created
    Postconditions: The graph objects contains a deep copy of the content of obj1
    */
   Graph(Graph& obj1);
   /**
    //-------------------------- Destructor  for class graph ------------------------------------//
    Preconditions:A graph object is created
    Postconditions: deallocate the elements stored in the Graph class
    */
   virtual ~Graph();
   /**
    //-------------------------- Overloaded assignment operator =  ------------------------------------//
    Preconditions: A graph object is created
    Postconditions: *this is assigned the same data as in the right object but at a different memory location
    @return graph object which is a deep copy of the object right
    */
   const Graph operator= (const Graph& right);
   /**
    //-------------------------------- buildGraph ---------------------------------//
    Builds a graph by reading data from an ifstream
    Preconditions:  infile has been successfully opened and the file contains  properly formated data (according to the program specs)
    Postconditions: One graph is read from infile and stored in the object
    **/
   void buildGraph(std::ifstream& file);
   /**
    //-------------------------- insertEdge ------------------------------------//
    Preconditions:A graph object is created and verices array is filled with vertex
    Postconditions: An edgeNode is created and added to the list of edge connected to edgeHead of is correponding vertexNode
    or replace any previous edge that existed between the two vertices by changing just the weight of the edgeNode
    */
   void insertEdge(int src, int dest, int weight);
   /**
    //-------------------------- removeEdge ------------------------------------//
    Preconditions:A graph object is created with vertices and edgeNodes
    Postconditions: removes an edge whose adjVertex is equal to destination in the src vertex of the vertices array
    @return boolean true if successfully removed or false if edge doesnt exist
    */
   bool removeEdge(int, int);
   /**
    //-------------------------- findShortestPath ------------------------------------//
    method that computes all shortest paths
    Preconditions: A Graph object is created and the object is built with vertices and edges using the buildGraph method
    Postconditions: uses a priority queue to compute shortest path between all vertices and fills the contents in Table T[][]
    */
   void findShortestPath();
   /**
    //-------------------------- display ------------------------------------//
    Preconditions:A graph is created, built and shortest Paths have been computed
    Postconditions: Output description from to dist and path. path is obtained using recusive helper method findPath()
    */
   void display(int start, int end) const;
   /**
    //-------------------------- displayAll ------------------------------------//
    Preconditions:A graph is created, built and shortest Paths have been computed
    Postconditions: Output a table formatted with description from to dist and path. path is obtained using recusive helper method findPath()
    */
   void displayAll() const;
   
};

#endif /* Graph_hpp */
