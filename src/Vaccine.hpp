//
//  Vaccine.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-01-30.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef Vaccine_hpp
#define Vaccine_hpp

//Vaccine struct definition
struct Vaccine {
    //public fields
    int numInitialAdopters;
    double scalingFactor; //scales edge weights in ICM model
    int dailyVaccinationCount; //number of individuals getting vaccinated daily
    int startVaccinationDate; //start date of vaccinations
    int maxVaccines; //maximum number of vaccines provided
    int incubationPeriod; //number of days until vaccination takes effect
    double efficacyRate; //percent of time vaccine takes effect
    
    //constructors
    Vaccine(){
        this->numInitialAdopters = 0;
        this->scalingFactor = 0;
        this->dailyVaccinationCount = 0;
        this->startVaccinationDate = 0;
        this->maxVaccines = 0;
        this->incubationPeriod = 0;
        this->efficacyRate = 0;
    }
    
    Vaccine(int numInitialAdopters, double scalingFactor, int dailyVaccinationCount, int startVaccinationDate, int maxVaccines, int incubationPeriod, double efficacyRate) {
        this->numInitialAdopters = numInitialAdopters;
        this->scalingFactor = scalingFactor;
        this->dailyVaccinationCount = dailyVaccinationCount;
        this->startVaccinationDate = startVaccinationDate;
        this->maxVaccines = maxVaccines;
        this->incubationPeriod = incubationPeriod;
        this->efficacyRate = efficacyRate;
    }
};
#endif /* Vaccine_hpp */
