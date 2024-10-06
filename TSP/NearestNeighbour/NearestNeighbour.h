//
// Created by Kuba on 06/10/2024.
//

#ifndef PEA_NEARESTNEIGHBOUR_H
#define PEA_NEARESTNEIGHBOUR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../Tree/Node/Node.h"

using namespace std;

class NearestNeighbour {
public:
    int result = INT_MAX;
    vector<int> best_way = vector<int>();
    int nearestNeighbour(Node start, int sum, vector<int> visited, int count, int size, int startNumb);
    void findBestWay(vector<Node> nodes);
};


#endif //PEA_NEARESTNEIGHBOUR_H
