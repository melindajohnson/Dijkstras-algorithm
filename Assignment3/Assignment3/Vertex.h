//
//  Vertex.hpp
//  Assignment3
//
//  Created by Melinda Johnson on 2/11/20.
//  Copyright © 2020 Melinda Johnson. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp
#include <stdio.h>
#include <iostream>
#include <string>
class Vertex{
private:
      std::string description;
         //friend std::istream& operator>>(std::istream& in, Vertex& obj1);
public:
   std::string getVertexData() const ;
   void setVertexData(std::string content);
   
};
#endif /* Vertex_hpp */
