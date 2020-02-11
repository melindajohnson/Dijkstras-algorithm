
//assume that the input is properly formatted
#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include "Vertex.h"

class Graph {
public:
   
private:
   static const int MAX_VERTICES = 5;
   
   struct EdgeNode {         // can change to a class, if desired
      int adjVertex;         // subscript of the adjacent vertex
      int weight;            // weight of edge
      EdgeNode *nextEdge = nullptr;
   };
   
    

   
   struct VertexNode {
      EdgeNode *edgeHead = nullptr;      // head of the list of edges
      Vertex *data ;      // store vertex data here
   };
   
      // table of information for Dijkstra's algorithm
   struct Table {
      bool visited = false ;         // whether vertex has been visited
      int dist = INT_MAX;            // shortest known distance from source
      int path = 0;            // previous vertex in path of min dist
   };
     
   VertexNode vertices[MAX_VERTICES];  // array of VertexNodes
   int size;               // number of vertices in the graph
   Table T[MAX_VERTICES][MAX_VERTICES];
      // stores visited, distance, path -
      // two dimensional in order to solve
      // for all sources
   
public:
   /**
    //-------------------------- Default constructor for class Graph ------------------------------------//
    Preconditions: None
    Postconditions:
    */
   Graph();
   /**
    //-------------------------- Copy constructor for class Graph ------------------------------------//
    Preconditions:
    Postconditions:
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
    //-------------------------- buildGraph ------------------------------------//
    Preconditions:
    Postconditions:
    */
   void buildGraph(std::ifstream& file);
   /**
    //-------------------------- insertEdge ------------------------------------//
    Preconditions:
    Postconditions:
    */
   //For insertEdge, replace any previous edge that existed between the two vertices.
   void insertEdge(int src, int dest, int weight);
   /**
    //-------------------------- removeEdge ------------------------------------//
    Preconditions:
    Postconditions:
    */
   void removeEdge(int, int);
   /**
    //-------------------------- findShortestPath ------------------------------------//
    Preconditions:
    Postconditions:
    */
   void findShortestPath(); //method that computes all shortest paths
   //Use recursion, not a container to display a path. Remember that you work backwards from the destination to the source to recover the path.
   /**
    //-------------------------- display ------------------------------------//
    Preconditions:
    Postconditions:
    */
   int MinDistVertex(int src);
   
   void display(int start, int end) const;
   /**
    //-------------------------- displayAll ------------------------------------//
    Preconditions:
    Postconditions:
    */
   void displayAll() const; //output a table formatted with description from to dist and path
   
   void printPath(int src, int dest)const;
   
   void printPathDescription(int src, int dest) const;
};

#endif /* Graph_hpp */
