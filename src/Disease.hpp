//
//  Disease.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-30.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef Disease_hpp
#define Disease_hpp

#include <vector>


//Disease struct definition
struct Disease {
    
    //public fields
    int numInitialInfections;
    int incubationPeriod;
    double fatalityRate;
    std::vector<std::pair<int, int> > recoveryTime;
    std::vector<std::vector<double> > transmissionRates;
    
    //default struct constructor
    Disease(){
        this->numInitialInfections = 0;
        this->incubationPeriod = 0;
        this->fatalityRate = 0;
    }
    
};
#endif /* Disease_hpp */
