//
// Created by Kuba on 04/10/2024.
//

#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H

#include <iostream>
#include <vector>
#include <chrono>
#include "../../Tree/Node/Node.h"
#include "../pomocnicze/usunWspolne.h"

using namespace std;

class BruteForce {
public:
    int result = INT_MAX;
    bool overTime = false;
    int timeLimit;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    vector<int> best_way = vector<int>();
    int bruteForce(Node start,int sum, vector<int> visited,int count, int size,int startNumb);
    void findBestWay(vector<Node> nodes);
};


#endif //PEA_BRUTEFORCE_H
