//
//  Ages.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-24.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "Ages.hpp"
#include <iostream>

int Ages::convertAgeRangeToGroup(int ageRange){
    //check age ranges until lower bound of age range is greater than or equal to lower bounds of age group
    for (int i = 0; i < ageGroups.size(); i++){
        if (this->ageRanges[ageRange] >= this->ageGroups[i]){
            return i;
        }
    }
    
    std::cout << "WARNING: Age group not found for age range " << ageRange << ". Returning -1." << std::endl;
    return -1;
}