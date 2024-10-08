//
// Created by Kuba on 07/10/2024.
//

#include "Config.h"

void Config::openJSON(string filename) {
    ifstream jsonFile;
    jsonFile.open("../config/configFiles/"+filename);

    if(jsonFile.is_open()){
        data = json::parse(jsonFile);
    }

}

void Config::loadConfig(string fileName) {
    openJSON(fileName);


    for(int x = 0; x < data["files"].size(); x++){
        files.push_back(make_pair(data["files"][x]["file_name"],data["files"][x]["optimum"]));
    }
    percentOfRandomTest = data["percent_of_random_test"];
    repetitionsPerInstance = data["repetitions_per_instance"];
    outputFile = data["output_file"];
    progressBar = data["progress_bar"];
    showNodesInConsole = data["show_nodes_in_console"];
}

