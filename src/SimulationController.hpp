//
//  SimulationController.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-30.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef SimulationController_hpp
#define SimulationController_hpp

#include <vector>
#include <string>
#include "Graph.hpp"
#include "Disease.hpp"
#include "DiseaseSpread.hpp"
#include "Vaccine.hpp"
#include "Statistics.hpp"
#include "SimulationParameters.hpp"
#include "FileReader.hpp"
#include "ContactNetwork.hpp"

//SimulationController class definition
class SimulationController {
public:
    //constructors and destructors
    SimulationController();
    ~SimulationController();
    
    //public methods
    void runTrial(SimulationParameters &simParams);
    void runSimulation(std::string masterFilePath);
    void initGraph();
    void clearGraph();
    void initStatistics();
    Statistics& getStatistics();
    
private:
    std::vector<Statistics> statistics;
};

#endif /* SimulationController_hpp */
