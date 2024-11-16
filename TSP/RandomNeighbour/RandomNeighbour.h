//
// Created by Kuba on 06/10/2024.
//

#ifndef PEA_RANDOMNEIGHBOUR_H
#define PEA_RANDOMNEIGHBOUR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../../Tree/Node/Node.h"
#include <algorithm>
#include <chrono>
#include <stdexcept>

using namespace std;

class RandomNeighbour {
public:
    bool overTime = false;
    int timeLimit;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    int result = INT_MAX;
    vector<int> best_way = vector<int>();
    void randomNeighbour( vector<Node> Nodes);
};


#endif //PEA_RANDOMNEIGHBOUR_H
