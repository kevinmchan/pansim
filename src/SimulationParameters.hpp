//
//  SimulationParameters.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-16.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef SimulationParameters_hpp
#define SimulationParameters_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Vaccine.hpp"
#include "Disease.hpp"
#include "Ages.hpp"

struct SimulationParameters {
    int numTrials;
    int numDays;
    std::string scenarioName;
    std::string inputDirectory;
    std::string outputDirectory;
    Vaccine vaccine;
    Disease disease;
    Ages ages;
    double indirectHouseholdContact;
    double indirectSchoolContact;
    double probHospitalization;
    double studentTeacherRatio;

    std::vector<int> censusDivisionRanges; //upper bounds
    
    std::vector<double> commuterProbByDisseminationArea;
    std::vector<std::vector<double> > workerTypeDistributionByDisseminationArea;
    std::vector<double> workplaceDistributionByDisseminationArea;
    
    std::vector<std::vector<double> > commuterRouteDistribution;
    std::vector<std::vector<int> > commuterRouteMapping;
    
    std::vector<int> workplaceContactDurationByType;
    std::vector<std::vector<int> > householdContactDurationByAge;
    std::vector<std::vector<int> > communityContactDurationByAge;
    std::vector<std::vector<int> > hospitalContactDurationByAge;
    std::vector<std::vector<int> > fluCentreContactDurationByAge;
    std::vector<std::vector<int> > primaryCareContactDurationByAge;
    std::vector<std::vector<int> > healthcareContactFrequencyByAge;
    
    std::vector<std::pair<int,double> > workplaceSizesDistribution;
    
    std::vector<std::vector<int> > schoolContactDurationByLevel;
    std::vector<std::vector<int> > communityContactFrequencyByAge;
    std::vector<int> workplaceContactFrequencyByType;
    
    std::vector<std::vector<double> > ageDistribution;
    std::vector<std::vector<std::vector<double> > > householdStructureDistribution;
    std::vector<std::vector<int> > householdSizeFrequency;
    
    std::vector<int> subwayRoutesByDisseminationArea;
    std::vector<int> transitContactDurationByRoute;
    
    std::vector<std::vector<std::pair<int,double> > > hospitalCensusMapping;
    std::vector<int> hospitalNurseDemand;
    std::vector<int> hospitalDoctorDemand;
    
    std::vector<std::vector<std::pair<int,double> > > fluCenterCensusMapping;
    std::vector<int> fluCenterNurseDemand;
    std::vector<int> fluCenterDoctorDemand;
    
    std::vector<int> primCareDoctorDemand;
    std::vector<int> primCareNurseDemand;
    
    std::vector<int> schoolEnrolment;
    std::vector<std::vector<std::vector<std::pair<int,double> > > > schoolLevelDisseminationAreaIDMapping;
};

#endif /* SimulationParameters_hpp */
