//
//  Ages.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-24.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef Ages_hpp
#define Ages_hpp

#include <stdio.h>
#include <vector>

//Ages class definition
class Ages {
public:
    
    //public methods
    int convertAgeRangeToGroup(int ageRange);
    int generateChildAgeGroup();
    int generateAdultAgeGroup();
    int generateParentAgeGroup(int childAgeGroup);
    
    //getters and setters
    int getNumAgeRanges(){
        return (int)this->ageRanges.size();
    }
    
    void setNumAgeRanges(int numAgeRanges){
        this->ageRanges.resize(numAgeRanges);
    }
    
    int getNumAgeGroups(){
        return (int)this->ageGroups.size();
    }
    
    void setNumAgeGroups(int numAgeGroups){
        this->ageGroups.resize(numAgeGroups);
    }
    
    void setAgeRanges(std::vector<int> ageRanges){
        this->ageRanges = ageRanges;
    }
    
    void setAgeGroups(std::vector<int> ageGroups){
        this->ageGroups = ageGroups;
    }
    
private:
    std::vector<int> ageRanges; //age range lower bounds
    std::vector<int> ageGroups; //age group lower bounds
};


#endif /* Ages_hpp */
