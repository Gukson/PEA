#include <iostream>
#include "data/data_loader/DataLoader.h"
#include "config/configClass/Config.h"
#include "TSP/TSPSolver/TSPSolver.h"
using namespace std;



int main() {

    Config c = Config();
    c.loadConfig("config.json");

    TSPSolver solver = TSPSolver();
    solver.testAlgoritms(c);

    return 0;
}
