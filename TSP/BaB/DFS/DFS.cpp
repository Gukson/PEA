//
// Created by Kuba on 23/10/2024.
//

#include "DFS.h"

int DFS::dfs(Node start, int sum, vector<int> visited, int count, int size, int startNumb) {

    if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
        timeLimit) {
        throw std::runtime_error("przekroczono limit czasowy");
    }

    if (sum > result) {
        return INT_MAX;
    }

    if (count == size && visited.size() == size) {
        for (pair<Node *, int> p: start.getVectorOfNodes()) {
            if (p.first->get_value() == startNumb) {
                result = min(sum + p.second, result);
                if (result == sum + p.second) {
                    visited.push_back(startNumb);
                    best_way = visited;
                }
            }
        }
    }

    int min_cost = INT_MAX;

    for (pair<Node *, int> p: start.getVectorOfNodes()) {
        auto it = find(visited.begin(), visited.end(), p.first->get_value());
        if (it == visited.end()) {
            vector<int> w = vector<int>(visited);
            w.push_back(p.first->get_value());
            int new_cost = dfs(*p.first, sum + p.second, w, count + 1, size, startNumb);
            min_cost = min(min_cost, new_cost);
        }
    }
    return min_cost;
}

void DFS::findBestWay(vector<Node> nodes) {
    overTime = false;
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    NearestNeighbour n = NearestNeighbour();

    vector<Node*> visited2 = vector<Node*>();
    n.nearestNeighbour(&nodes[0],nodes.size(),visited2);
    result = n.result;
    vector<int> visited = vector<int>();
    visited.push_back(0);
    dfs(nodes[0], 0, visited, 1, nodes.size(), 0);
    best_scores.push_back(result);
    best_ways.push_back(best_way);
    result = INT_MAX;
    best_way.clear();

    auto min_it = std::min_element(best_scores.begin(), best_scores.end());
    result = *min_it;
    auto it = std::find(best_scores.begin(), best_scores.end(), *min_it);
    int index = distance(best_scores.begin(), it);
    best_way = best_ways[index];
}