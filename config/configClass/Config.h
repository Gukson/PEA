//
// Created by Kuba on 07/10/2024.
//

#ifndef PEA_CONFIG_H
#define PEA_CONFIG_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



using namespace std;
class Config {
public:
    vector<pair<string,int>> files;
    int percentOfRandomTest;
    int repetitionsPerInstance;
    string outputFile;
    bool progressBar;
    bool showNodesInConsole;
    void loadConfig(string fileName);
private:
    void openJSON(string fileName);
    json data;


};


#endif //PEA_CONFIG_H
