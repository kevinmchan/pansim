//
//  main.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-27.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "time.h"
#include "SimulationController.hpp"
#include <ctime>

void test1();

int main(int argc, const char * argv[]) {
   
    SimulationController simController = SimulationController();
    simController.runSimulation("/Users/kevinchan/Desktop/morPop/morPop/data/modelParams_1.txt");
    
}