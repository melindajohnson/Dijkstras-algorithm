//
//  Graph.hpp
//  Assignment3
//
//  Created by Melinda Johnson on 2/4/20.
//  Copyright © 2020 Melinda Johnson. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>

class Graph {
public:
   
private:
   static const int MAX_VERTICES = 101;
   
   struct EdgeNode {         // can change to a class, if desired
      int adjVertex;         // subscript of the adjacent vertex
      int weight;            // weight of edge
      EdgeNode *nextEdge;
   };
   
   struct VertexNode {
      EdgeNode *edgeHead;      // head of the list of edges
      Vertex *data;      // store vertex data here
   };
   
      // array of VertexNodes
   VertexNode vertices[MAX_VERTICES];
   
      // table of information for Dijkstra's algorithm
   struct Table {
      bool visited;         // whether vertex has been visited
      int dist;            // shortest known distance from source
      int path;            // previous vertex in path of min dist
   };
   
   int size;               // number of vertices in the graph
   Table T[MAX_VERTICES][MAX_VERTICES];
      // stores visited, distance, path -
      // two dimensional in order to solve
      // for all sources
};

#endif /* Graph_hpp */
