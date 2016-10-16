//
//  Statistics.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-30.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef Statistics_hpp
#define Statistics_hpp

#include <stdio.h>
#include <string>
#include "SimulationParameters.hpp"

//Statistics class definition
struct Statistics {
    SimulationParameters simParams;
    std::string model;
    int totalInfections;
    int totalVaccinations;
    int peakDay;
    int peakInfections;
};
#endif /* Statistics_hpp */
