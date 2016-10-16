//
//  VaccineAdoption.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-31.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "VaccineAdoption.hpp"
#include <set>

VaccineAdoption::VaccineAdoption(Vaccine vaccine) {
    //Copy vaccine parameters
    this->vaccine = vaccine;
    
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    this->engine = std::mt19937(rd());
}

VaccineAdoption::~VaccineAdoption() {}

void VaccineAdoption::getDailyAdopters(std::vector<Vertex*> &outputVertices, int day){
    if ( (day >= 0) && (day < this->dailyAdoptors.size()) ) {
        outputVertices = this->dailyAdoptors[day];
    }
}


void VaccineAdoption::setAdoptionThresholds(ContactNetwork &graph) {
    
    //update vertices with a vaccine adoption threshold
    std::uniform_real_distribution<double> realDist(0, 1);
    std::vector<Vertex*> vertices = graph.getVertices();
    for (std::vector<Vertex*>::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
        
        (*vertex)->setAdoptionThreshold(realDist(this->engine));
    
    }
}

void VaccineAdoption::runLTM(ContactNetwork &graph, int numSeeds) {
    //set initial adoption thresholds
    setAdoptionThresholds(graph);
    
    //set initial adoptors seeds
    initSeeds(graph, numSeeds);
    
    //cascade LTM until no more activations
    while (cascadeLTMAdoption());
}

void VaccineAdoption::runRandomAdoption(ContactNetwork &graph) {
    this->adopters = graph.getVertices();
    std::random_shuffle(this->adopters.begin(), this->adopters.end());
}

void VaccineAdoption::runICM(ContactNetwork &graph, int numSeeds, double scaling) {
    
    //set initial adoptors seeds
    initSeeds(graph, numSeeds);
    
    //cascade LTM until no more activations
    while (cascadeICMAdoption(scaling));
}

bool VaccineAdoption::cascadeICMAdoption(double scaling){
    bool foundNewAdopter = false;
    
    // find non-adoptor neighbours of all recent adopters
    std::vector<Vertex*> &recentAdopters = this->dailyAdoptors.back();
    std::vector<Vertex*> newAdopters;
    
    //across all recent adopters
    for (std::vector<Vertex*>::iterator vertex = recentAdopters.begin(); vertex != recentAdopters.end(); ++vertex) {
        std::vector<Edge*> edges = (*vertex)->getEdges();
        
        //across all neighbours of recent adopters
        for (std::vector<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            Vertex* neighbour = (*edge)->getNeighbour();
            double prob = (*edge)->getWeight()*scaling;
            
            //check that neighbour is not already an adopter
            if (!neighbour->getIsVaccineAdopter()) {
                
                //flip coin to cascade vaccine sentiment
                std::uniform_real_distribution<double> realDist(0, 1);
                if (prob >= realDist(this->engine)) {
                    foundNewAdopter = true;
                    (neighbour)->setIsVaccineAdpoter(true);
                    newAdopters.push_back(neighbour);
                }
            }
        }
    }
    
    //if found a new adopter, push back vector of new adopters
    if (foundNewAdopter) {
        this->dailyAdoptors.push_back(newAdopters);
        this->adopters.insert(this->adopters.begin(), newAdopters.begin(), newAdopters.end());
    }
    
    return foundNewAdopter;
}

bool VaccineAdoption::cascadeLTMAdoption(){
    bool foundNewAdopter = false;
    
    // find non-adoptor neighbours of all recent adopters
    std::set<Vertex*> candidates; //set used because candidate may be influenced by multiple recent adopters
    std::vector<Vertex*> &recentAdopters = this->dailyAdoptors.back();
    std::vector<Vertex*> newAdopters;
    
    //across all recent adopters
    for (std::vector<Vertex*>::iterator vertex = recentAdopters.begin(); vertex != recentAdopters.end(); ++vertex) {
        std::vector<Edge*> edges = (*vertex)->getEdges();
        
        //across all neighbours of recent adopters
        for (std::vector<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            Vertex* neighbour = (*edge)->getNeighbour();
            
            //add to candidate list if not already an adopter
            if (!neighbour->getIsVaccineAdopter()) {
                candidates.insert(neighbour);
            }
        }
    }
    
    // check if candidate is activated
    for (std::set<Vertex*>::iterator candidate = candidates.begin(); candidate != candidates.end(); ++candidate) {
        std::vector<Edge*> edges = (*candidate)->getEdges();
        
        double totalWeight = 0;
        double adoptersWeight = 0;
        
        //sum weights across all neighbours of candidate
        for (std::vector<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            Vertex* neighbour = (*edge)->getNeighbour();
            double weight = (*edge)->getWeight();
            
            //add weight to total adopters weight, if neighbour is adopter
            if (neighbour->getIsVaccineAdopter()) {
                adoptersWeight += weight;
            }
            totalWeight += weight;
        }
        
        //if weight ratio passes threshold, add candidate to new adopters
        if (adoptersWeight/totalWeight >= (*candidate)->getAdoptionThreshold()){
            foundNewAdopter = true;
            (*candidate)->setIsVaccineAdpoter(true);
            newAdopters.push_back(*candidate);
        }
    }
    
    //if found a new adopter, push back vector of new adopters
    if (foundNewAdopter) {
        this->dailyAdoptors.push_back(newAdopters);
        this->adopters.insert(this->adopters.begin(), newAdopters.begin(), newAdopters.end());
    }
    
    return foundNewAdopter;
}

void VaccineAdoption::initSeeds(ContactNetwork &graph, int numSeeds) {
    
    std::uniform_int_distribution<int> intDist(0, graph.getNumVertices()-1); //subtract by 1 to account for zero indexing
    std::vector<Vertex*> seedVertices;
    
    for (int i = 0; i < numSeeds; i++) {
        //draw candidate
        int seedCandidate = intDist(engine);
        Vertex* candidate = graph.getVertices()[seedCandidate];
        
        //check if candidate is already in vector of seed individuals
        if(std::find(seedVertices.begin(), seedVertices.end(), candidate) != seedVertices.end()) {
            i--; //repeat step since candidate already added to seeds
        } else {
            candidate->setIsVaccineAdpoter(true);
            seedVertices.push_back(candidate);
        }
    }
    this->dailyAdoptors.push_back(seedVertices);
    this->adopters.insert(this->adopters.end(), seedVertices.begin(), seedVertices.end());
}

void VaccineAdoption::makeVaccinated(Vertex &vertex) {
    //update to vaccinated only if currently susceptable
    if (vertex.getHealthStatus()==SUSCEPTABLE) {
        vertex.setHealthStatus(VACCINATED);
        this->numVaccinations++;
    }
}

void VaccineAdoption::sendToVaccinate(std::vector<Vertex*> &adopters, int maxDailyVaccines, int maxTotalVaccines) {
    
    int numVaccinators = 0;
    std::vector<Vertex*>::iterator iter;
    
    //iterate across adopters and send for adoption
    for (iter = adopters.begin(); iter!=adopters.end(); ++iter) {
        
        // check for max total vaccines
        if (this->numVaccinations >= maxTotalVaccines) {
            return;
        }
        
        // check for max daily vaccines
        if (numVaccinators >= maxDailyVaccines) {
            ++iter;
            break;
        }
        
        // check that individual is susceptable
        if ((*iter)->getHealthStatus()==SUSCEPTABLE) {
            (*iter)->setHealthStatus(VACCINATED);
            this->numVaccinations++;
            numVaccinators++;
        }
    }
    
    //remove today's adopters from vector
    adopters.erase(adopters.begin(), iter);
}

void VaccineAdoption::reset() {
    this->adopters.clear();
    this->dailyAdoptors.clear();
}