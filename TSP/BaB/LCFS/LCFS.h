#ifndef PEA_2_LCFS_H
#define PEA_2_LCFS_H

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include "../../../Tree/Node/Node.h"
#include "../../pomocnicze/usunWspolne.h"
#include "../../../TSP/NearestNeighbour/NearestNeighbour.h"
#include <queue>
#include <chrono>

using namespace std;

class LCFS {
public:
    struct Kolejkowicz {
        Node* node;
        vector<Node*> way;
        int cost;

        // Konstruktor z inicjalizacją
        Kolejkowicz(Node* n, int c) : node(n), cost(c) {
            way.push_back(n);
        }

        Kolejkowicz(Node *n,vector<Node*> w,int c ): node(n), cost(c), way(std::move(w)){}

        bool operator<(const Kolejkowicz& other) const {
            return cost > other.cost;  // Mniejszy koszt ma wyższy priorytet
        }
    };
    void findBestWay(vector<Node> nodes);
    void lcfs(Node start, int size);
    int result = INT_MAX;
    bool overTime = false;
    int timeLimit;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    vector<int> best_way = vector<int>();

};


#endif //PEA_2_LCFS_H
