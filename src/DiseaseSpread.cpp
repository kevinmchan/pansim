//
//  DiseaseSpread.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-29.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "DiseaseSpread.hpp"
#include <iostream>
#include <random>

DiseaseSpread::DiseaseSpread(Disease disease) {
    this->disease = disease;
    this->numInfections = 0;
    this->numFatalities = 0;
    this->numRecoveries = 0;
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    this->engine = std::mt19937(rd());
}

DiseaseSpread::~DiseaseSpread() {}

void DiseaseSpread::updateDailySpread(){
    
    //for each exposed individual, update incubation count; update to infectious
    updateExposureStatus();
    
    //for each infectious individual, update recovery time; update to recovered
    updateInfectiousStatus();
    
    //for infectious individuals, cascade disease to neighbours
    cascadeDisease();
    
    //print number of active infectious
    //std::cout << "Number of infectious: " << this->infectious.size() << std::endl;
    //std::cout << "Number of exposed: " << this->exposed.size() << std::endl;
    //std::cout << "Number of vaccinated: " << this->numVaccinations << std::endl;
}

void DiseaseSpread::cascadeDisease(){
    
    //setup random generator
    std::uniform_real_distribution<double> realDist(0, 1);
    
    //across infectious individuals, cascade disease to neighbours
    for (std::vector<Vertex*>::iterator vertex = this->infectious.begin(); vertex != this->infectious.end(); ++vertex) {
        
        std::vector<Edge*> edges = (*vertex)->getEdges();
        
        for (std::vector<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            
            //check if neighbour is susceptable
            Vertex* neighbour = (*edge)->getNeighbour();
            if (neighbour->getHealthStatus() == SUSCEPTABLE) {
                
                //get transmission rate based on age groups
                int fromAge = (*vertex)->getAgeGroup();
                int toAge = neighbour->getAgeGroup();
                
                //flip coin for exposure
                double weight = (*edge)->getWeight();
                if (this->disease.transmissionRates[fromAge][toAge]*weight > realDist(engine)) {
                    makeExposed(*neighbour);
                }
            }
        }
    }
}

void DiseaseSpread::updateExposureStatus(){
    //container for new infectious individuals
    std::vector<Vertex*> newInfectious;
    
    //increment exposure days and update infectious status
    std::sort(this->exposed.begin(), this->exposed.end()); //sort to be able to perform set difference later; newInfectious will also be sorted
    for (std::vector<Vertex*>::iterator it = this->exposed.begin(); it != this->exposed.end(); ++it) {
        //increment exposure day count
        (*it)->incrementDaysSinceExposed();
        
        //update to infectious status
        if ((*it)->getDaysSinceExposed() >= this->disease.incubationPeriod) {
            newInfectious.push_back(*it);
        }
    }
    
    //update new infectious individuals
    std::vector<Vertex*> newInfectiousVector(newInfectious.begin(), newInfectious.end());
    updateStatus(newInfectiousVector, INFECTIOUS);
    
    //remove infectious from exposed vector
    std::vector<Vertex*> remainingExposed;
    std::set_difference(this->exposed.begin(), this->exposed.end(), newInfectious.begin(), newInfectious.end(), std::inserter(remainingExposed, remainingExposed.end()));
    this->exposed = remainingExposed;
}

void DiseaseSpread::updateInfectiousStatus(){
    //container for new recovered individuals
    std::vector<Vertex*> newRecovered;
    
    //increment exposure days and update infectious status
    std::sort(this->infectious.begin(), this->infectious.end()); //sort to be able to perform set difference later; newInfectious will also be sorted
    for (std::vector<Vertex*>::iterator it = this->infectious.begin(); it != this->infectious.end(); ++it) {
        
        //update to recovered status
        if ((*it)->getDaysSinceInfectious() >= (*it)->getRecoveryTime()) {
            newRecovered.push_back(*it);
            continue;
        }
        
        //increment exposure day count
        (*it)->incrementDaysSinceInfectious();
    }
    
    //update new infectious individuals
    std::vector<Vertex*> recoveredVector(newRecovered.begin(), newRecovered.end());
    updateStatus(recoveredVector, RECOVERED);
    
    //remove recovered from infectious vector
    std::vector<Vertex*> remainingInfectious;
    std::set_difference(this->infectious.begin(), this->infectious.end(), newRecovered.begin(), newRecovered.end(), std::inserter(remainingInfectious, remainingInfectious.end()));
    this->infectious = remainingInfectious;
}

std::vector<Vertex*> DiseaseSpread::initSpread(ContactNetwork &graph) {
    
    //create vector to hold initial infections
    std::vector<Vertex*> initialInfections;
    
    //std::cout << "Initializing " << numSeeds << " seeds" << std::endl;
    std::uniform_int_distribution<int> intDist(0, graph.getNumVertices()-1); //subtract by 1 to account for zero indexing
    
    for (int i = 0; i < disease.numInitialInfections; i++) {
        //draw candidate
        int seedCandidate = intDist(engine);
        Vertex* candidate = graph.getVertices()[seedCandidate];
        
        //check if candidate is already in vector of infectious individuals
        if(std::find(this->infectious.begin(), this->infectious.end(), candidate) != this->infectious.end()) {
            i--; //repeat step since candidate already infectious
            //std::cout << "Duplicated seed produced" << std::endl;
        } else {
            makeInfectious(*candidate);
            initialInfections.push_back(candidate);
        }
    }
    //print number of active infectious
    //std::cout << "Number of infectious: " << this->infectious.size() << std::endl;
    //std::cout << "Number of exposed: " << this->exposed.size() << std::endl;
    //std::cout << "Number of vaccinated: " << this->numVaccinations << std::endl;
    
    return initialInfections;
}

void DiseaseSpread::initSpread(Disease &disease, std::vector<Vertex*> &initialInfections) {

    //set vector of initial seeds as infectious
    for (std::vector<Vertex*>::iterator it = initialInfections.begin(); it != initialInfections.end(); ++it) {
        makeInfectious(**it);
    }
    //print number of active infectious
    //std::cout << "Number of infectious: " << this->infectious.size() << std::endl;
    //std::cout << "Number of exposed: " << this->exposed.size() << std::endl;
    //std::cout << "Number of vaccinated: " << this->numVaccinations << std::endl;
}


void DiseaseSpread::updateStatus(std::vector<Vertex*> &vertices, HealthStatus healthStatus) {
    for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        switch (healthStatus) {
            
            case EXPOSED:
                makeExposed(**it);
                break;
            
            case INFECTIOUS:
                makeInfectious(**it);
                break;
                
            case RECOVERED:
                makeRecovered(**it);
                break;
                
            default:
                std::cout << "WARNING: Health status is not recognized!" << std::endl;
                break;
        }
    }
}

void DiseaseSpread::makeExposed(Vertex &vertex) {
    vertex.setHealthStatus(EXPOSED);
    vertex.setDaysSinceExposed(0);
    //add vertex to vector of infectious vertices
    this->exposed.push_back(&vertex);
}

void DiseaseSpread::makeRecovered(Vertex &vertex) {
    vertex.setHealthStatus(RECOVERED);
    this->numRecoveries++;
}

void DiseaseSpread::makeInfectious(Vertex &vertex) {
    vertex.setHealthStatus(INFECTIOUS);
    
    //add vertex to vector of infectious vertices
    this->infectious.push_back(&vertex);
    this->numInfections++;
    
    //set days since infectious
    vertex.setDaysSinceInfectious(0);
    
    //set recovery time
    setRecoveryTime(vertex);
}

void DiseaseSpread::setRecoveryTime(Vertex &vertex) {
    //get age group
    int ageGroup = vertex.getAgeGroup();
    
    //set recovery time
    std::uniform_int_distribution<int> intDist(this->disease.recoveryTime[ageGroup].first, this->disease.recoveryTime[ageGroup].second);
    vertex.setRecoveryTime(intDist(engine));
}

void DiseaseSpread::resetHealthStatus(ContactNetwork &graph) {
    
    //reset health status across all vertices
    for (std::vector<Vertex*>::iterator iter = graph.getVertices().begin(); iter != graph.getVertices().end(); ++iter) {
        (*iter)->setHealthStatus(SUSCEPTABLE);
        (*iter)->setAdoptionThreshold(0);
        (*iter)->setRecoveryTime(0);
    }
}

void DiseaseSpread::reset() {
    this->numInfections = 0;
    this->numFatalities = 0;
    this->numRecoveries = 0;
    this->exposed.clear();
    this->infectious.clear();
}