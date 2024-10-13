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

using namespace std;

class RandomNeighbour {
public:
    bool over30min = false;
    int timeLimit;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    int result = INT_MAX;
    vector<int> best_way = vector<int>();
    void randomNeighbour(int filesPermutation, vector<Node> Nodes);
};


#endif //PEA_RANDOMNEIGHBOUR_H
