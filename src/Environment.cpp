//
//  Environment.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-26.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "Environment.hpp"

void Environment::addMember(Vertex* member){
    this->members.push_back(member);
}

void Environment::addMembers(std::vector<Vertex*> newMembers){
    this->members.insert(this->members.end(), newMembers.begin(), newMembers.end());
}