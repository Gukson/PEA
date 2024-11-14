//
// Created by Kuba on 23/10/2024.
//

#ifndef PEA_2_DFS_H
#define PEA_2_DFS_H
#include <iostream>
#include <vector>
#include <chrono>
#include "../../../Tree/Node/Node.h"


class DFS {
public:
    int result = INT_MAX;
    bool overTime = false;
    int timeLimit;
    int optimum;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    vector<int> best_way = vector<int>();
    int dfs(Node start, int sum, vector<int> visited, int count, int size, int startNumb);
    void findBestWay(vector<Node> nodes);
};


#endif //PEA_2_DFS_H
