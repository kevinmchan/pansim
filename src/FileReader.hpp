//
//  FileReader.hpp
//  morPop
//
//  Created by Kevin Chan on 2016-03-16.
//  Copyright © 2016 Kevin Chan. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "SimulationParameters.hpp"

//FileReader class definition
class FileReader {
public:
    //constructors and destructors
    FileReader(std::string FilePath);
    ~FileReader();
    
    //public methods
    bool loadParameters(SimulationParameters &simParamsOutput);
    
private:
    std::string masterFileDirectory;
    
    //file reading helper methods
    bool openFile(std::string filePath, std::ifstream &inputStream);
    
    void skipLines(std::ifstream &inputStream, int numLines);
    
    template<typename T>
    T readValue(std::ifstream &inputStream, int leadingLines);
    
    template<typename T>
    void readMatrix(int matrixSize, std::ifstream &inputStream, int leadingLines, std::vector<std::vector<T> > &matrixOutput);
    
    template<typename T>
    void readMatrix(int nRows, int nCols, std::ifstream &inputStream, int leadingLines, std::vector<std::vector<T> > &matrixOutput);
    
    template<typename T>
    void readMatrix(int nRows, int nCols, std::ifstream &inputStream, int leadingCols, int leadingLines, std::vector<std::vector<T> > &matrixOutput);
    
    template<typename T>
    void readRow(int length, std::ifstream &inputStream, int leadingLines, std::vector<T> &rowOutput);
    
    //file readers
    bool loadScenarioFile(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadVaccinationParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadDiseaseParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadPopulationParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadAgeDistribution(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHouseholdStructures(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHouseholdSizes(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadSubwayRoutes(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadRoutesData(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHealthAuthorityParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHealthParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadNurseContactDurations(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadPatientContactDuratiions(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHospitalContactFrequency(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHealthAuthorityData(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadHospitalParams(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadFluCentreData(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadVaccinationDestinations(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadPrimData(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadMasterSchools(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadJuniorSchools(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadIntermediateSchools(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadSeniorSchools(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadCensusDivisionMapping(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadWorkerTypeDistribution(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadWorkerContactDurations(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadWorkplaceSizeDistribition(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadWorkplaceDisseminationAreaDistribution(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadCommuterRouteDistribution(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadCommuterRouteMapping(std::string filePath, SimulationParameters &simParamsOutput);
    bool loadDisseminationAreaDistances(std::string filePath, SimulationParameters &simParamsOutput);
};

#endif /* FileReader_hpp */
