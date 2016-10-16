//
//  FileReader.cpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-16.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#include "FileReader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

//Macro definitions
#define NUM_CENSUS_DIVISIONS 5
#define SCHOOL_MEMBER_GROUPS 2
#define STUDENT_GROUP 0
#define TEACHER_GROUP 1
#define STUDENT_GROUP_LEVELS 3
#define WORKING_AGE_GROUP 2
#define STUDENT_AGE_GROUP 1
#define NUM_WORKPLACE_TYPES 5
#define NUM_DISSEMINATION_AREAS 7685
#define NUM_HOUSEHOLD_SIZES 6
#define NUM_HOUSHOLD_TYPES 3
#define NUM_TRANSIT_ROUTES 20
#define NUM_HOSPITALS 33
#define SCHOOL_ID_OFFSET 1000
#define JUNIOR 0
#define INTERMEDIATE 1
#define SENIOR 2
#define NUM_SCHOOLS 2233
#define NUM_WORKPLACE_SIZES 8

FileReader::FileReader(std::string FilePath) {
    this->masterFileDirectory = FilePath;
}

FileReader::~FileReader() {
    
}


bool FileReader::loadParameters(SimulationParameters &simParamsOutput) {

    //open master parameters file
    std::ifstream inputStream;
    inputStream.open(masterFileDirectory.c_str(), std::ifstream::in);
    
    //check that stream opened successfully
    if(inputStream.fail()){
        std::cout << "ERROR: " << masterFileDirectory << " could not be opened!" << std::endl;
        return false;
    }
    
    //Instantiate file reader helpers
    int integerBuffer;
    std::string stringBuffer;
    
    /*** Read master parameters ***/
    
    //Get number of simulations
    skipLines(inputStream, 1);
    inputStream >> integerBuffer;
    simParamsOutput.numTrials = integerBuffer;
    
    //Get number of days
    skipLines(inputStream, 3);
    inputStream >> integerBuffer;
    simParamsOutput.numDays = integerBuffer;
    
    //Get scenario names
    skipLines(inputStream, 3);
    inputStream >> stringBuffer;
    simParamsOutput.scenarioName = stringBuffer;
    
    //Get input directory
    skipLines(inputStream, 3);
    inputStream >> stringBuffer;
    simParamsOutput.inputDirectory = stringBuffer;

    //Get input directory
    skipLines(inputStream, 3);
    inputStream >> stringBuffer;
    simParamsOutput.outputDirectory = stringBuffer;
    
    //Get file paths
    std::vector<std::string> fileNames;
    int numPaths = 31;
    
    for(int i = 0; i < numPaths; i++) {
        skipLines(inputStream, 3);
        inputStream >> stringBuffer;
        fileNames.push_back(stringBuffer);
    }
    
    //Close input stream
    inputStream.close();
    
    /*** Load data files ***/
    int fileCount = 0;
    loadScenarioFile(fileNames[fileCount++], simParamsOutput);
    loadPopulationParams(fileNames[fileCount++], simParamsOutput);
    loadVaccinationParams(fileNames[fileCount++], simParamsOutput);
    loadDiseaseParams(fileNames[fileCount++], simParamsOutput);
    loadAgeDistribution(fileNames[fileCount++], simParamsOutput);
    loadHouseholdStructures(fileNames[fileCount++], simParamsOutput);
    loadHouseholdSizes(fileNames[fileCount++], simParamsOutput);
    loadSubwayRoutes(fileNames[fileCount++], simParamsOutput);
    loadRoutesData(fileNames[fileCount++], simParamsOutput);
    loadHealthAuthorityParams(fileNames[fileCount++], simParamsOutput);
    loadHealthParams(fileNames[fileCount++], simParamsOutput);
    loadNurseContactDurations(fileNames[fileCount++], simParamsOutput);
    loadPatientContactDuratiions(fileNames[fileCount++], simParamsOutput);
    loadHospitalContactFrequency(fileNames[fileCount++], simParamsOutput);
    loadHealthAuthorityData(fileNames[fileCount++], simParamsOutput);
    loadHospitalParams(fileNames[fileCount++], simParamsOutput);
    loadFluCentreData(fileNames[fileCount++], simParamsOutput);
    loadVaccinationDestinations(fileNames[fileCount++], simParamsOutput);
    loadPrimData(fileNames[fileCount++], simParamsOutput);
    loadMasterSchools(fileNames[fileCount++], simParamsOutput);
    loadJuniorSchools(fileNames[fileCount++], simParamsOutput);
    loadIntermediateSchools(fileNames[fileCount++], simParamsOutput);
    loadSeniorSchools(fileNames[fileCount++], simParamsOutput);
    loadCensusDivisionMapping(fileNames[fileCount++], simParamsOutput);
    loadWorkerTypeDistribution(fileNames[fileCount++], simParamsOutput);
    loadWorkerContactDurations(fileNames[fileCount++], simParamsOutput);
    loadWorkplaceSizeDistribition(fileNames[fileCount++], simParamsOutput);
    loadWorkplaceDisseminationAreaDistribution(fileNames[fileCount++], simParamsOutput);
    loadCommuterRouteDistribution(fileNames[fileCount++], simParamsOutput);
    loadCommuterRouteMapping(fileNames[fileCount++], simParamsOutput);
    loadDisseminationAreaDistances(fileNames[fileCount++], simParamsOutput);
    return true;
}

//scenarioParams_1.txt
bool FileReader::loadScenarioFile(std::string filePath, SimulationParameters &simParamsOutput) {
    
    //Open parameters file
    std::ifstream inputStream;
    std::cout << "Loading scenario parameters" << std::endl;
    filePath = simParamsOutput.inputDirectory + filePath;
    inputStream.open(filePath.c_str(),std::ifstream::in);
    
    //Check that file opened successfully
    if(inputStream.fail())
    {
        std::cout << "ERROR! File " << filePath << " could not be opened." << std::endl;
        return false;
    }

    //Instantiate helpers
    int integerBuffer;
    double floatBuffer;
    
    /*** Get scenario parameters ***/
    
    try {
        //Get number of initital infections
        skipLines(inputStream, 1);
        inputStream >> integerBuffer;
        simParamsOutput.disease.numInitialInfections = integerBuffer;
        
        //Get vaccine efficacy
        skipLines(inputStream, 9);
        inputStream >> floatBuffer;
        simParamsOutput.vaccine.efficacyRate = floatBuffer;
        
        //Get indirect household contact
        skipLines(inputStream, 10);
        inputStream >> floatBuffer;
        simParamsOutput.indirectHouseholdContact = floatBuffer;
        
        //Get indirect school contact
        skipLines(inputStream, 3);
        inputStream >> floatBuffer;
        simParamsOutput.indirectSchoolContact = floatBuffer;
        
        //Get vaccine delay
        skipLines(inputStream, 3);
        inputStream >> integerBuffer;
        simParamsOutput.vaccine.incubationPeriod = integerBuffer;

    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Scenario plan file read successfully \n");
    return true;
}

//vaccineParams.txt
bool FileReader::loadVaccinationParams(std::string filePath, SimulationParameters &simParamsOutput){
    
    //Open parameters file
    std::ifstream inputStream;
    std::cout << "Loading vaccine parameters" << std::endl;
    filePath = simParamsOutput.inputDirectory + filePath;
    inputStream.open(filePath.c_str(),std::ifstream::in);
    
    //Check that file opened successfully
    if(inputStream.fail())
    {
        std::cout << "ERROR! File " << filePath << " could not be opened." << std::endl;
        return false;
    }
    
    //Instantiate helpers
    int integerBuffer;
    double floatBuffer;
    
    /*** Get scenario parameters ***/
    
    try {
        //Get number of initital vaccinators
        skipLines(inputStream, 1);
        inputStream >> integerBuffer;
        simParamsOutput.vaccine.numInitialAdopters = integerBuffer;
        
        //Get scaling factor
        skipLines(inputStream, 3);
        inputStream >> floatBuffer;
        simParamsOutput.vaccine.scalingFactor = floatBuffer;
        
        //Get number of daily vaccinations
        skipLines(inputStream, 3);
        inputStream >> integerBuffer;
        simParamsOutput.vaccine.dailyVaccinationCount = integerBuffer;
        
        //Get vaccination start date
        skipLines(inputStream, 3);
        inputStream >> integerBuffer;
        simParamsOutput.vaccine.startVaccinationDate = integerBuffer;
        
        //Get max number of vaccines
        skipLines(inputStream, 3);
        inputStream >> integerBuffer;
        simParamsOutput.vaccine.maxVaccines = integerBuffer;
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Scenario plan file read successfully \n");
    return true;
    
}

//diseaseParams.txt
bool FileReader::loadDiseaseParams(std::string filePath, SimulationParameters &simParamsOutput){
    
    //Open parameters file
    std::ifstream inputStream;
    std::cout << "Loading disease parameters" << std::endl;
    filePath = simParamsOutput.inputDirectory + filePath;
    inputStream.open(filePath.c_str(),std::ifstream::in);
    
    //Check that file opened successfully
    if(inputStream.fail())
    {
        std::cout << "ERROR! File " << filePath << " could not be opened." << std::endl;
        return false;
    }
    
    //Instantiate helpers
    int integerBuffer;
    
    /*** Get disease parameters ***/
    
    try {
        //Get disease fatality rate
        simParamsOutput.disease.fatalityRate = readValue<double>(inputStream, 1);
        
        //Get disease transmission rates by age group
        readMatrix(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.disease.transmissionRates);
        
        //Get infectious period by age group
        skipLines(inputStream, 3);
        int min, max;
        for (int i = 0; i < simParamsOutput.ages.getNumAgeGroups(); i++){
            inputStream >> min >> max;
            simParamsOutput.disease.recoveryTime.push_back(std::pair<int, int>(min,max));
        }
        
        //Get disease latent period
        skipLines(inputStream, 3);
        inputStream >> integerBuffer;
        simParamsOutput.disease.incubationPeriod = integerBuffer;
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Scenario plan file read successfully \n");
    return true;
    
}

//populationParams.txt
bool FileReader::loadPopulationParams(std::string filePath, SimulationParameters &simParamsOutput){

    //Open parameters file
    std::ifstream inputStream;
    std::cout << "Loading disease parameters" << std::endl;
    filePath = simParamsOutput.inputDirectory + filePath;
    inputStream.open(filePath.c_str(),std::ifstream::in);
    
    //Check that file opened successfully
    if(inputStream.fail())
    {
        std::cout << "ERROR! File " << filePath << " could not be opened." << std::endl;
        return false;
    }
    
    //Instantiate helpers
    int integerBuffer;
    
    /*** Get population parameters ***/
    
    try {
        
        //Get number of age ranges
        skipLines(inputStream, 12);
        inputStream >> integerBuffer;
        std::vector<int> ageRanges(integerBuffer);
        
        //Get age ranges
        skipLines(inputStream, 3);
        for (int i = 0; i < ageRanges.size(); i++){
            inputStream >> integerBuffer;
            ageRanges[i] = integerBuffer;
        }
        simParamsOutput.ages.setAgeRanges(ageRanges);
        
        //Get number of age groups
        std::vector<int> ageGroups(readValue<int>(inputStream, 3));
        
        //Get age groups
        skipLines(inputStream, 3);
        for (int i = 0; i < ageGroups.size(); i++){
            inputStream >> integerBuffer;
            ageGroups[i] = integerBuffer;
        }
        simParamsOutput.ages.setAgeGroups(ageGroups);
        
        //Get household contact duration
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.householdContactDurationByAge);
        
        //Get community contact duration
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.communityContactDurationByAge);
        
        //Get hospital contact duration
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.hospitalContactDurationByAge);
        
        //Get flu center contact duration
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.fluCentreContactDurationByAge);
        
        //Get primary care contact duration
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.primaryCareContactDurationByAge);
        
        //Get community contact frequency
        readMatrix<int>(simParamsOutput.ages.getNumAgeGroups(), inputStream, 3, simParamsOutput.communityContactFrequencyByAge);
        
        //Get school contact duration
        readMatrix<int>(SCHOOL_MEMBER_GROUPS, STUDENT_GROUP_LEVELS, inputStream, 3, simParamsOutput.schoolContactDurationByLevel);
        
        //Get work contact frequency
        skipLines(inputStream, 18);
        for (int i = 0; i < NUM_WORKPLACE_TYPES; i++){
            inputStream >> integerBuffer;
            simParamsOutput.workplaceContactFrequencyByType.push_back(integerBuffer);
        }
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Population params file read successfully \n");
    return true;
    
}

//Age_Dissemination.txt
bool FileReader::loadAgeDistribution(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        readMatrix<double>(NUM_DISSEMINATION_AREAS, simParamsOutput.ages.getNumAgeRanges(), inputStream, 1, 1, simParamsOutput.ageDistribution);
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
}

//GTA_HH_Structures.txt
bool FileReader::loadHouseholdStructures(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get household structures distribution ***/
    
    try {
        
        //read structures
        skipLines(inputStream, 1);
        
        //create vector for dissemination areas
        simParamsOutput.householdStructureDistribution = std::vector<std::vector<std::vector<double> > >(NUM_DISSEMINATION_AREAS);
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            //skip leading token
            int integerBuffer;
            inputStream >> integerBuffer;
            
            //create vector for household sizes
            simParamsOutput.householdStructureDistribution[i] = std::vector<std::vector<double> >(NUM_HOUSEHOLD_SIZES);
            
            //for each household size
            for (int j = 0; j < NUM_HOUSEHOLD_SIZES; j++) {
                
                //create vector for household structures
                simParamsOutput.householdStructureDistribution[i][j] = std::vector<double>(NUM_HOUSHOLD_TYPES);
                
                //for each household structure
                for (int k = 0; k < NUM_HOUSHOLD_TYPES; k++) {
                    double floatBuffer;
                    inputStream >> floatBuffer;
                    simParamsOutput.householdStructureDistribution[i][j][k] = floatBuffer;
                }
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;

}

//GTA_HH_Dissemination_Sizes.txt
bool FileReader::loadHouseholdSizes(std::string filePath, SimulationParameters &simParamsOutput){

    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get household size distribution ***/
    
    try {
        
        //read structures
        skipLines(inputStream, 1);
        
        //create vector for dissemination areas
        simParamsOutput.householdSizeFrequency = std::vector<std::vector<int> >(NUM_DISSEMINATION_AREAS);
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            //skip leading token
            int integerBuffer;
            inputStream >> integerBuffer;
            
            //create vector for household sizes
            simParamsOutput.householdSizeFrequency[i] = std::vector<int>(NUM_HOUSEHOLD_SIZES);
            
            //for each household size
            for (int j = 0; j < NUM_HOUSEHOLD_SIZES; j++) {
                inputStream >> integerBuffer;
                simParamsOutput.householdSizeFrequency[i][j] = integerBuffer;
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//subwayRoutes_disseminationAreas.txt
bool FileReader::loadSubwayRoutes(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get subway routes ***/
    
    try {
        
        //read structures
        skipLines(inputStream, 1);
        
        //create vector for dissemination areas
        simParamsOutput.subwayRoutesByDisseminationArea = std::vector<int>(NUM_DISSEMINATION_AREAS);
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            //skip leading token
            int integerBuffer, integerBuffer2;
            inputStream >> integerBuffer >> integerBuffer2;
            simParamsOutput.subwayRoutesByDisseminationArea[i] = integerBuffer2;
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//routeData.txt
bool FileReader::loadRoutesData(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get transit route parameters ***/
    
    try {

        skipLines(inputStream, 1);
        //create vector for dissemination areas
        simParamsOutput.transitContactDurationByRoute = std::vector<int>(NUM_TRANSIT_ROUTES);
        for (int i = 0; i < NUM_TRANSIT_ROUTES; i++) {
            
            //skip leading token
            int integerBuffer, integerBuffer2;
            inputStream >> integerBuffer >> integerBuffer2;
            simParamsOutput.subwayRoutesByDisseminationArea[integerBuffer] = integerBuffer2;
            
            //skip rest of line
            skipLines(inputStream, 1);
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//lhinParams.txt
bool FileReader::loadHealthAuthorityParams(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get lhin params ***/
    
    try {
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//healthParams.txt
bool FileReader::loadHealthParams(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get health paramaters ***/
    
    try {
        
        //get probability of hospitalization
        simParamsOutput.probHospitalization = readValue<double>(inputStream, 13);
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//ageContactDuration_hospital_nurse.txt
bool FileReader::loadNurseContactDurations(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get hospital nurse contact durations ***/
    
    try {
        
        //already implemented in population params
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//ageContactDuration_hospitalPatient.txt
bool FileReader::loadPatientContactDuratiions(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get patient contact durations ***/
    
    try {
        
        //already implemented in population params
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//ageContactNumber_hospital.txt
bool FileReader::loadHospitalContactFrequency(std::string filePath, SimulationParameters &simParamsOutput){
   
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get contact number for healthcare systems ***/
    
    try {
        
        readMatrix(4, inputStream, 0, simParamsOutput.healthcareContactFrequencyByAge);
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//LHINData.txt
bool FileReader::loadHealthAuthorityData(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get LHIN data distribution ***/
    
    try {
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//hospitalInfo.txt
bool FileReader::loadHospitalParams(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get hospital info ***/
    
    try {
        
        skipLines(inputStream, 11);
        int LHIN, maxPatients, numDoctors, numNurses;
        std::string name;
        double probVisit;
        
        simParamsOutput.hospitalCensusMapping = std::vector<std::vector<std::pair<int, double> > >(NUM_CENSUS_DIVISIONS);
        for (int i = 0; i < NUM_HOSPITALS; i++) {
            inputStream >> LHIN >> name >> maxPatients >> numDoctors >> numNurses >> probVisit;
            simParamsOutput.hospitalCensusMapping[LHIN].push_back(std::pair<int, double>(i, probVisit));
            simParamsOutput.hospitalNurseDemand.push_back(numNurses);
            simParamsOutput.hospitalDoctorDemand.push_back(numDoctors);
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//fluCentreData.txt
bool FileReader::loadFluCentreData(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get flu center data ***/
    
    try {
        
        //get number of flu centers
        int numFluCenters = readValue<int>(inputStream, 2);
        
        //get flu center parameters
        int LHIN, numDoctors, numNurses;
        std::string name;
        double probVisit;
        
        simParamsOutput.fluCenterCensusMapping = std::vector<std::vector<std::pair<int, double> > >(NUM_CENSUS_DIVISIONS);
        for (int i = 0; i < numFluCenters; i++) {
            inputStream >> LHIN >> name >> numDoctors >> numNurses >> probVisit;
            simParamsOutput.fluCenterCensusMapping[LHIN].push_back(std::pair<int, double>(i, probVisit));
            simParamsOutput.fluCenterNurseDemand.push_back(numNurses);
            simParamsOutput.fluCenterDoctorDemand.push_back(numDoctors);
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//vaccinationDestinations.txt
bool FileReader::loadVaccinationDestinations(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//primData.txt
bool FileReader::loadPrimData(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
        int LHIN, numDoctors, numNurses;
        skipLines(inputStream, 1);
        for (int i = 0; i < NUM_CENSUS_DIVISIONS; i++) {
            inputStream >> LHIN >> numDoctors >> numNurses;
            simParamsOutput.primCareDoctorDemand.push_back(numDoctors);
            simParamsOutput.primCareNurseDemand.push_back(numNurses);
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//GTA_Schools_All.txt
bool FileReader::loadMasterSchools(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
        //get student teacher ratio
        simParamsOutput.studentTeacherRatio = readValue<double>(inputStream, 1);
        
        //get school enrollment numbers
        int schoolID, level, boardID, enrolment;
        std::string schoolName, boardName;
        
        simParamsOutput.schoolEnrolment = std::vector<int>(NUM_SCHOOLS);
        for (int i = 0; i < NUM_SCHOOLS; i++){
            inputStream >> schoolID >> level >> schoolName >> boardName >> boardID >> enrolment;
            simParamsOutput.schoolEnrolment[i] = enrolment;
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//GTA_Schools_Junior.txt
bool FileReader::loadJuniorSchools(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get school distribution ***/
    
    try {
        
        skipLines(inputStream, 1);
        simParamsOutput.schoolLevelDisseminationAreaIDMapping.push_back(std::vector<std::vector<std::pair<int, double> > >(NUM_DISSEMINATION_AREAS));
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            int disseminationArea, numSchools, schoolID;
            float prob;
            
            //read number of schools
            inputStream >> disseminationArea >> numSchools;
            
            //get school id and prob
            for (int j = 0; j < numSchools; j++) {
                inputStream >> schoolID >> prob;
                simParamsOutput.schoolLevelDisseminationAreaIDMapping[JUNIOR][i].push_back(std::pair<int,double>(schoolID - 1000, prob));
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//GTA_Schools_Intermediate.txt
bool FileReader::loadIntermediateSchools(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
        skipLines(inputStream, 1);
        simParamsOutput.schoolLevelDisseminationAreaIDMapping.push_back(std::vector<std::vector<std::pair<int, double> > >(NUM_DISSEMINATION_AREAS));
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            int disseminationArea, numSchools, schoolID;
            float prob;
            
            //read number of schools
            inputStream >> disseminationArea >> numSchools;
            
            //get school id and prob
            for (int j = 0; j < numSchools; j++) {
                inputStream >> schoolID >> prob;
                simParamsOutput.schoolLevelDisseminationAreaIDMapping[INTERMEDIATE][i].push_back(std::pair<int,double>(schoolID - 1000, prob));
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//GTA_Schools_Senior.txt
bool FileReader::loadSeniorSchools(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
        skipLines(inputStream, 1);
        simParamsOutput.schoolLevelDisseminationAreaIDMapping.push_back(std::vector<std::vector<std::pair<int, double> > >(NUM_DISSEMINATION_AREAS));
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            
            int disseminationArea, numSchools, schoolID;
            float prob;
            
            //read number of schools
            inputStream >> disseminationArea >> numSchools;
            
            //get school id and prob
            for (int j = 0; j < numSchools; j++) {
                inputStream >> schoolID >> prob;
                simParamsOutput.schoolLevelDisseminationAreaIDMapping[SENIOR][i].push_back(std::pair<int,double>(schoolID - 1000, prob));
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//Census_Division_Mapping.txt
bool FileReader::loadCensusDivisionMapping(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get census division ranges (Dissemination Area upperbound) ***/
    
    try {
        
        //census division ranges
        readRow(5, inputStream, 1, simParamsOutput.censusDivisionRanges);
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//DAIndex.txt
bool FileReader::loadWorkerTypeDistribution(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get commuter and worker type distribution ***/
    
    try {
        
        skipLines(inputStream, 1);
        
        int disseminationArea;
        float prob;
        
        simParamsOutput.commuterProbByDisseminationArea = std::vector<double>(NUM_DISSEMINATION_AREAS);
        simParamsOutput.workerTypeDistributionByDisseminationArea = std::vector<std::vector<double> >(NUM_DISSEMINATION_AREAS, std::vector<double>(NUM_WORKPLACE_TYPES));
        
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            inputStream >> disseminationArea >> prob;
            simParamsOutput.commuterProbByDisseminationArea[i] = prob;
            
            for (int j = 0; j < NUM_WORKPLACE_TYPES; j++) {
                inputStream >> prob;
                simParamsOutput.workerTypeDistributionByDisseminationArea[i][j] = prob;
            }
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//DAWorkClass.txt
bool FileReader::loadWorkerContactDurations(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get workplace contact duration ***/
    
    try {
        
        skipLines(inputStream, 1);
        
        for (int i = 0; i < NUM_WORKPLACE_TYPES; i++) {
            int workplaceType, duration;
            float hazardRate;
            
            inputStream >> workplaceType >> duration >> hazardRate;
            
            simParamsOutput.workplaceContactDurationByType.push_back(duration);
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//Workplace_Office_Sizes.txt
bool FileReader::loadWorkplaceSizeDistribition(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get office size distribution ***/
    
    try {
        
        skipLines(inputStream, 1);
        for (int i = 0; i < NUM_WORKPLACE_SIZES; i++) {
            int size;
            float prob;
            inputStream >> size >> prob;
            
            simParamsOutput.workplaceSizesDistribution.push_back(std::pair<int, float>(size, prob));
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//workplacesbyDA.txt
bool FileReader::loadWorkplaceDisseminationAreaDistribution(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get commuter and worker type distributions ***/
    
    try {
        
        skipLines(inputStream, 1);
        int disseminationArea;
        double prob;
        simParamsOutput.workplaceDistributionByDisseminationArea = std::vector<double>(NUM_DISSEMINATION_AREAS);
        for (int i = 0; i < NUM_DISSEMINATION_AREAS; i++) {
            inputStream >> disseminationArea >> prob;
            simParamsOutput.workplaceDistributionByDisseminationArea[i] = prob;
        }
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//Commuter_Distribution.txt
bool FileReader::loadCommuterRouteDistribution(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get commuter distribution ***/
    
    try {
        
        readMatrix<double>(NUM_CENSUS_DIVISIONS, inputStream, 1, simParamsOutput.commuterRouteDistribution);
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//go_Transit_Route.txt
bool FileReader::loadCommuterRouteMapping(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get transit route mapping ***/
    
    try {
        
        readMatrix<int>(NUM_CENSUS_DIVISIONS, inputStream, 1, simParamsOutput.commuterRouteMapping); 
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}

//DAUID_Distances.txt
bool FileReader::loadDisseminationAreaDistances(std::string filePath, SimulationParameters &simParamsOutput){
    
    //open file
    std::ifstream inputStream;
    if(!openFile(simParamsOutput.inputDirectory + filePath, inputStream)){
        return false;
    }
    
    /*** Get age distribution ***/
    
    try {
        
    } catch (std::exception e) {
        return false;
    }
    
    //Close input stream
    inputStream.close();
    printf("Age distribution file read successfully \n");
    return true;
    
}


//helper functions
bool FileReader::openFile(std::string filePath, std::ifstream &inputStream) {
    //Open parameters file
    std::cout << "Loading file " << filePath << std::endl;
    inputStream.open(filePath.c_str(),std::ifstream::in);
    
    //Check that file opened successfully
    if(inputStream.fail())
    {
        std::cout << "ERROR! File " << filePath << " could not be opened." << std::endl;
        return false;
    }
    return true;
}

void FileReader::skipLines(std::ifstream &inputStream, int numLines) {
    std::string buffer;
    for (int i = 0; i < numLines; i++)
    {
        getline(inputStream, buffer);
    }
}

template<typename T>
T FileReader::readValue(std::ifstream &inputStream, int leadingLines){
    T buffer;
    skipLines(inputStream, leadingLines);
    inputStream >> buffer;
    return buffer;
}

template<typename T>
void FileReader::readMatrix(int matrixSize, std::ifstream &inputStream, int leadingLines, std::vector<std::vector<T> > &matrixOutput){
    readMatrix<T>(matrixSize, matrixSize, inputStream, leadingLines, matrixOutput);
}

template<typename T>
void FileReader::readMatrix(int nRows, int nCols, std::ifstream &inputStream, int leadingCols, int leadingLines, std::vector<std::vector<T> > &matrixOutput){
    T buffer;
    skipLines(inputStream, leadingLines);
    //get rows
    for (int i = 0; i < nRows; i++){
        std::vector<T> row;
        //eat leading columns
        for (int j = 0; j < leadingCols; j++){
            inputStream >> buffer;
        }
        //get column values
        for (int j = 0; j < nCols; j++){
            inputStream >> buffer;
            row.push_back(buffer);
        }
        matrixOutput.push_back(row);
    }
}

template<typename T>
void FileReader::readMatrix(int nRows, int nCols, std::ifstream &inputStream, int leadingLines, std::vector<std::vector<T> > &matrixOutput){
    readMatrix<T>(nRows, nCols, inputStream, 0, leadingLines, matrixOutput);
}

template <typename T>
void FileReader::readRow(int length, std::ifstream &inputStream, int leadingLines, std::vector<T> &rowOutput) {
    T buffer;
    skipLines(inputStream, leadingLines);
    for (int i = 0; i < length; i++){
        inputStream >> buffer;
        rowOutput.push_back(buffer);
    }
}
