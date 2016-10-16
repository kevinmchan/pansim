//
//  Environment.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-26.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp

#include <stdio.h>
#include <vector>
#include "Vertex.hpp"

//Environment class definition
class Environment {
public:
    
    //public methods
    void addMember(Vertex* newMember);
    void addMembers(std::vector<Vertex*> newMembers);
    
    //getters and setters
    void setMembers(std::vector<Vertex*> members){
        this->members = members;
    }
    
    std::vector<Vertex*> getMembers(){
        return this->members;
    }
    
protected:
    
    //protected members
    std::vector<Vertex*> members;
};

#endif /* Environment_hpp */
