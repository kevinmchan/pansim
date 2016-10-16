//
//  SimulationController.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-30.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include <iostream>
#include <random>
#include "SimulationController.hpp"
#include "VaccineAdoption.hpp"

SimulationController::SimulationController(){}

SimulationController::~SimulationController(){}

void SimulationController::runSimulation(std::string masterFilePath) {
    
    // Load simulation model parameters
    FileReader fileReader = FileReader(masterFilePath);
    SimulationParameters simParams = SimulationParameters();
    bool successful = fileReader.loadParameters(simParams);

    // Check if parameters loading was successful
    if (!successful) {
        std::cout << "There has been an error loading the parameters. Exiting simulation." << std::endl;
        return;
    }
    
    // Run simulation trials
    for (int trial = 0; trial < simParams.numTrials; trial++) {
        runTrial(simParams);
    }
}

void SimulationController::runTrial(SimulationParameters &simParams) {
    
    /*** Generate contact network ***/
    
    // Start timer for graph initalization
    time_t timer;
    time(&timer);
    
    ContactNetwork *contactNetwork = new ContactNetwork();
    contactNetwork->generateNetwork(simParams);
    //contactNetwork->printEdges();
    
    // Get time to initialize contact network
    std::cout << "Time to initialize contact network is " << difftime(time(NULL), timer) << " seconds" << std::endl;

    
    /*** Initialize vaccine adoption ***/
    
    // Start timer for vaccine uptake modelling
    time(&timer);
    
    // Initialize vaccine adoption model
    VaccineAdoption vaccineAdoption = VaccineAdoption(simParams.vaccine);
    
    // Run ICM model
    vaccineAdoption.runICM(*contactNetwork, simParams.vaccine.numInitialAdopters, simParams.vaccine.scalingFactor);
    std::vector<Vertex*> vaccineAdopters = vaccineAdoption.getAdopters();
    
    // Get time to run vaccine adoption model
    std::cout << "Time to run trial is " << difftime(time(NULL), timer) << " seconds" << std::endl;
    
    
    /*** Initialize disease spread ***/
    
    // Initialize disease spread model
    DiseaseSpread diseaseSpread = DiseaseSpread(simParams.disease);
    
    // Get disease spread seeds
    std::vector<Vertex*> initialInfections = diseaseSpread.initSpread(*contactNetwork);
    
    // run daily disease spread
    int peakDay = 0;
    int peakInfections = 0;
    int currentInfections = 0;
    for (int day = 0; day < simParams.numDays; day++) {
        //std::cout << "Day " << day + 1 << " of " << this->numDays << std::endl;
        
        //update vaccines while vaccination has started and all vaccinations have not been used
        if ((day >= simParams.vaccine.startVaccinationDate) && (vaccineAdoption.getNumVaccinations() < simParams.vaccine.maxVaccines) && (vaccineAdopters.size() > 0)) {
            vaccineAdoption.sendToVaccinate(vaccineAdopters, simParams.vaccine.dailyVaccinationCount, simParams.vaccine.maxVaccines);
        }
        
        //update diseaseSpread
        diseaseSpread.updateDailySpread();
        currentInfections = diseaseSpread.getCurrentInfections();
        if (currentInfections > peakInfections) {
            peakInfections = currentInfections;
            peakDay = day;
        }
        
    }
    
    
    /*** Record stats for trial ***/
    
    Statistics stats = Statistics();
    stats.simParams = simParams;
    stats.totalInfections = diseaseSpread.getNumInfections();
    stats.totalVaccinations = vaccineAdoption.getNumVaccinations();
    stats.peakDay = peakDay;
    stats.peakInfections = peakInfections;
    stats.model = "ICM_ORDERED";
    this->statistics.push_back(stats);
    
    std::cout << "End of trial, with " << diseaseSpread.getNumInfections() << " infections, " << diseaseSpread.getNumRecoveries() << " recoveries and " << vaccineAdoption.getNumVaccinations() << " vaccinations" << std::endl;
    

    /*** Clean up at end of trial ***/
    // Start timer for graph cleaning
    time(&timer);
    
    // clean up
    delete contactNetwork;
    
    // Get time to delete graph
    std::cout << "Time to clear graph is " << difftime(time(NULL), timer) << " seconds" << std::endl;
}