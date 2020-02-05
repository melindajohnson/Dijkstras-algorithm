//
//  Graph.cpp
//  Assignment3
//
//  Created by Melinda Johnson on 2/4/20.
//  Copyright © 2020 Melinda Johnson. All rights reserved.
//

#include <fstream>
#include "Graph.h"
using namespace std;


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
      infile.getline(..., ..., '\n');      // read descriptions (use of this method is not mandatory)
      ...                                  // store appropriately
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

