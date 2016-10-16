//
//  VaccineAdoption.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-31.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef VaccineAdoption_hpp
#define VaccineAdoption_hpp

#include <stdio.h>
#include <vector>
#include <random>
#include "Vertex.hpp"
#include "ContactNetwork.hpp"
#include "Vaccine.hpp"

//VaccineAdoption class definition
class VaccineAdoption {
public:
    //constructors and destructors
    VaccineAdoption(Vaccine vaccine);
    ~VaccineAdoption();
    
    //public methods
    void getDailyAdopters(std::vector<Vertex*> &outputVertices, int day); //return vector of vacciners for the day
    
    void runICM(ContactNetwork &graph, int numSeeds, double scaling);
    void runRandomAdoption(ContactNetwork &graph);
    
    //generate daily adoptors for FixedLTM
    void generateDynamicLTMSchedule(ContactNetwork &graph, int numSeeds); //determine daily adopters
    void generateFixedLTMSchedule(ContactNetwork &graph, int numSeeds, int numDays); //determine daily adopters
    void generateRandomSchedule(ContactNetwork &graph, int totalAdoptors, std::vector<int> &adoptionSchedule);
    
    //LTM methods
    void runLTM(ContactNetwork &graph, int numSeeds); //set initial adoptors
    
    bool cascadeLTMAdoption(); //cascade influence to get new adoptors; return whether there are any new adopters
    
    bool cascadeICMAdoption(double scaling); //cascade influence to get new adoptors; return whether there are any new adopters
    
    void vaccineFixedRandom(int numVacciners); //
    void vaccineFixedLTM(int day); //
                       
    void initSeeds(ContactNetwork &graph, int numSeeds); //set initial adoptors
    void setAdoptionThresholds(ContactNetwork &graph);
    void makeVaccinated(Vertex &vertex);
    void sendToVaccinate(std::vector<Vertex*> &adopters, int maxDailyVaccines, int maxTotalVaccines);
    void reset();
    
    //getters and setters
    std::vector<Vertex*>& getAdopters() {
        return this->adopters;
    }
        
    int getNumVaccinations() {
        return this->numVaccinations;
    }
    
private:
    Vaccine vaccine;
    std::vector<Vertex*> adopters;
    std::vector<std::vector<Vertex*> > dailyAdoptors;
    std::mt19937 engine;
    int numVaccinations;
};
#endif /* VaccineAdoption_hpp */