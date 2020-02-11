//
//  Vertex.cpp
//  Assignment3
//
//  Created by Melinda Johnson on 2/11/20.
//  Copyright © 2020 Melinda Johnson. All rights reserved.
//

#include "Vertex.h"
std::string Vertex::getVertexData() const {
   return description;
}
void Vertex::setVertexData(std::string content){
   description = content;
}
