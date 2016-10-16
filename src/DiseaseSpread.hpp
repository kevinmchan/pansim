//
//  DiseaseSpread.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-29.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef DiseaseSpread_hpp
#define DiseaseSpread_hpp

#include <random>
#include "ContactNetwork.hpp"
#include "Disease.hpp"

//DiseaseSpread class definition
class DiseaseSpread {
public:
    //constructors and destructors
    DiseaseSpread(Disease disease);
    ~DiseaseSpread();
    
    //public methods
    std::vector<Vertex*> initSpread(ContactNetwork &graph);
    void initSpread(Disease &disease, std::vector<Vertex*> &initialInfections);
    void updateDailySpread();
    void updateExposureStatus();
    void updateInfectiousStatus();
    void makeSusceptable(Vertex &vertex);
    void makeExposed(Vertex &vertex);
    void makeInfectious(Vertex &vertex);
    void makeRecovered(Vertex &vertex);
    void makeDeceased(Vertex &vertex);
    void cascadeDisease();
    void setRecoveryTime(Vertex &vertex);
    void updateStatus(std::vector<Vertex*> &vertices, HealthStatus healthStatus);
    void resetHealthStatus(ContactNetwork &graph);
    void reset();
    
    //getters and setters
    int getNumInfections() {
        return this->numInfections;
    }
    
    int getNumRecoveries() {
        return this->numRecoveries;
    }
    
    int getCurrentInfections() {
        return (int)this->infectious.size();
    }
    
private:
    Disease disease;
    int numInfections;
    int numFatalities;
    int numRecoveries;
    std::vector<Vertex*> exposed;
    std::vector<Vertex*> infectious;
    std::mt19937 engine;
};


#endif /* DiseaseSpread_hpp */
