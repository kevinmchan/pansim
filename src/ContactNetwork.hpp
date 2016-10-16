//
//  ContactNetwork.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-16.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef ContactNetwork_hpp
#define ContactNetwork_hpp

#include <stdio.h>
#include "SimulationParameters.hpp"
#include "Graph.hpp"
#include <random>

//ContactNetwork class definition
class ContactNetwork : public Graph {
public:
    
    //constructors and destructors
    ContactNetwork();
    ~ContactNetwork();
    
    void generateNetwork(SimulationParameters &simParams);
    
private:
    //private methods
    void generateHouseholds(SimulationParameters &simParams, std::vector<std::vector<std::vector<Vertex*> > > unassignedWorkers, std::vector<std::vector<std::vector<Vertex*> > > unassignedStudents);
    void generateHousehold(int structure, std::vector<Vertex*> unassignedWorkers, std::vector<Vertex*> unassignedStudents);
    
    //private members
    std::mt19937 engine;
};

#endif /* ContactNetwork_hpp */
