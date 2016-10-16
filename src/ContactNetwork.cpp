//
//  ContactNetwork.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-16.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "ContactNetwork.hpp"
#include "Household.hpp"
#include <vector>
#include "Community.hpp"
#include "HealthcareSystem.hpp"
#include "School.hpp"

//Constructor
ContactNetwork::ContactNetwork(){
    
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    this->engine = std::mt19937(rd());
    
}

//Destructor
ContactNetwork::~ContactNetwork(){
    
}

//Generates a contact network based on the simulation parameters
void ContactNetwork::generateNetwork(SimulationParameters &simParams) {
 
    
    /* create and connect households */
    //for each dissemination area:
        //for household size:
            //generate number of housholds:
                //draw household structure for household size
                    //generate number of children based on household size and structure
                        //generate age based on age distribution
                        //add to vector of unassigned students
                    //generate number of adults based on household structure and size
                        //genrate age based on age of children; parents are [18 + eldest, 40 + youngest] years
                        //if working age
                            //assign worker type based on worker distribution
                            //assign commuter type based on commuter distribution
                            //add to vector of unassigned workers
                    //add to community (dissemination area)
    
    /* connect members of communities */
    
    /* generate offices */
    //for each worker type
        //while capacity is less than number of unassigned individuals
            //create workplace in randomly assigned dissemination area and office size
    
    /* allocate workers to offices */
    //for each unassigned worker
        //if commuter, determine
    
    //for each census division:
        //generate workplace:
            //
    
    
    
    
    //container for community members by age group
    std::vector<std::vector<Community*> > communities;
    
    //container for unassigned workers by level and census areas
    std::vector<std::vector<std::vector<Vertex*> > > unassignedWorkers;
    
    //container for unassigned students by level and dissemination areas
    std::vector<std::vector<std::vector<Vertex*> > > unassignedStudents;
    
    //container for workplaces by level and census area with capacity
    std::vector<std::vector<std::vector<Workplace*> > > availableWorkplaces;
    
    //container for schools by level and dissemination area with capacity
    std::vector<std::vector<std::vector<School*> > > availableSchools;
    
    //create and connect households
    
    
    //create workplaces
    
    
    //create hospitals
    
    
    //create schools
    
    
    //assign nurses and doctors to hospitals
    
    
    //assign workers to workplaces
    
    
    //assign students to schools
    
    
    //connect community contacts
    
}

/*** 
    Implement morPop population code below
 ***/

void ContactNetwork::generateHouseholds(SimulationParameters &simParams, std::vector<std::vector<std::vector<Vertex*> > > unassignedWorkers, std::vector<std::vector<std::vector<Vertex*> > > unassignedStudents){
    
    //for each dissemination area
    for (int i = 0; i < simParams.householdSizeFrequency.size(); i++) {
        //for each household size
        for (int j = 0; j < simParams.householdSizeFrequency[i].size(); j++) {
            //for number of households
            for (int k = 0; k < simParams.householdSizeFrequency[i][j]; k++) {
                
                //draw household structure for size and dissemination area
                std::uniform_real_distribution<double> realDist(0, 1);
                double rand = realDist(this->engine);
                int structure;
                for (structure = 0; structure < simParams.householdStructureDistribution[i][j].size(); structure++){
                    if (rand < simParams.householdStructureDistribution[i][j][structure]) {
                        break;
                    }
                }
                
                generateHousehold(structure, unassignedWorkers, unassignedStudents);
                
            }
        }
    }
}

void ContactNetwork::generateHousehold(int structure, std::vector<std::vector<<#class _Tp#>>>, <#std::vector<std::vector<std::vector<Vertex *> > > unassignedStudents#>)