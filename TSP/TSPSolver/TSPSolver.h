//
// Created by Kuba on 07/10/2024.
//

#ifndef PEA_TSPSOLVER_H
#define PEA_TSPSOLVER_H

#include <iostream>
#include <vector>
#include <chrono> //liczenie czasu
#include <cmath> // wartośc bezwzględna
#include <fstream> //do plików
#include "../../TSP/bruteForce/BruteForce.h"
#include "../../TSP/NearestNeighbour/NearestNeighbour.h"
#include "../../TSP/RandomNeighbour/RandomNeighbour.h"
#include "../../config/configClass/Config.h"
#include "../../data/data_loader/DataLoader.h"

using namespace std;
class TSPSolver {
public:
    //klasy
    BruteForce b = BruteForce();
    NearestNeighbour n = NearestNeighbour();
    RandomNeighbour r = RandomNeighbour();

    //czas
    chrono::duration<double, std::milli> ms_double;
    vector<vector<double>> bruteForceTime = vector<vector<double>>();
    vector<vector<double>> nearTime = vector<vector<double>>();
    vector<vector<double>> randomTime = vector<vector<double>>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();

    //funkcje
    void testAlgoritms(Config config);
    void progressBar(int* progressSave,float* progress, int repetitions);
    vector<double> calcStats(vector<double> time);


};


#endif //PEA_TSPSOLVER_H
