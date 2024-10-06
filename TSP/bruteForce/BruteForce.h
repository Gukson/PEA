//
// Created by Kuba on 04/10/2024.
//

#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H

#include <iostream>
#include <vector>
#include "../../Tree/Node/Node.h"

using namespace std;

class BruteForce {
public:
    int result = INT_MAX;
    vector<int> best_wat = vector<int>();
    int bruteForce(Node start,int sum, vector<int> visited,int count, int size);
};


#endif //PEA_BRUTEFORCE_H
