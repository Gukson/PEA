//
// Created by Kuba on 23/10/2024.
//

#ifndef PEA_2_BFS_H
#define PEA_2_BFS_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "../../../Tree/Node/Node.h"
#include "../../pomocnicze/usunWspolne.h"
#include "../../../TSP/NearestNeighbour/NearestNeighbour.h"

using namespace std;

class BFS {
public:
    void findBestWay(vector<Node> nodes);
    void bfs(Node start, int size);
    int result = INT_MAX;
    bool overTime = false;
    int timeLimit;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    vector<int> best_way = vector<int>();
};


#endif //PEA_2_BFS_H
