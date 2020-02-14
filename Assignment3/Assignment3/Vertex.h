/**---------------------------------------------------------------------------
 VERTEX.H
 Declaration of the Vertex class
 Author: Melinda Stannah Stanley Jothiraj
 Student number- 1978413
 --------------------------------------------------------------------
 Vertex class :
 Holds the contents of a vertex
 Includes additional features :
 -- The class contains an accessor method to get contents of a Vertex Object
 -- The class contains a muttator method to set contents of a Vertex Object
 --------------------------------------------------------------------------------------------------------------------
 **/

#ifndef Vertex_hpp
#define Vertex_hpp
#include <stdio.h>
#include <iostream>
#include <string>\

class Vertex{
private:
   std::string description; //holds the data of the Vertex
public:
   /**
    //-------------------------- Accessor method------------------------------------//
    Preconditions: A Vertex object is created and description is set
    Postconditions: returns the string containing description
    @return description of type String
    */
   std::string getVertexData() const ;
   /**
    //-------------------------- Mutatator method------------------------------------//
    Preconditions: A Vertex object is created
    Postconditions: sets the description in the Objects
    */
   void setVertexData(std::string content);
   
};
#endif /* Vertex_hpp */
