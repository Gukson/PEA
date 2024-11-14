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

using namespace std;

class BFS {
public:
    void bfs(Node start, int size);
    int result = INT_MAX;
    bool overTime = false;
    int timeLimit;
};


#endif //PEA_2_BFS_H
