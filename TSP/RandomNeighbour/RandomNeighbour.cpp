#include "RandomNeighbour.h"

void RandomNeighbour::randomNeighbour(int filesPermutation, vector<Node> nodes) {
    random_device rd;
    mt19937 g(rd());
    overTime = false;
    for (int x = 0; x < filesPermutation; x++) {
        int score = 0;
        vector<int> way = vector<int>();
        shuffle(nodes.begin(), nodes.end(), g);
        for (int y = 0; y < nodes.size() - 1; y++) {
            bool found = false;
            for (pair<Node *, int> p: nodes[y].getVectorOfNodes()) {
                if (p.first->get_value() == nodes[y + 1].get_value()) {
                    score += p.second;
                    way.push_back(nodes[y].get_value());
                    found = true;
                    break;
                }
                if (std::chrono::duration_cast<std::chrono::minutes>(
                        std::chrono::high_resolution_clock::now() - time).count() >= timeLimit) {
                    throw std::runtime_error("przekroczono limit czasowy");
                }
            }
            if (!found) {
                break;
            }
        }
        if (way.size() == nodes.size() - 1) {
            bool found = false;
            for (pair<Node *, int> p: nodes[nodes.size() - 1].getVectorOfNodes()) {
                if (p.first->get_value() == nodes[0].get_value()) {
                    score += p.second;
                    way.push_back(nodes[nodes.size() - 1].get_value());
                    way.push_back(nodes[0].get_value());
                    found = true;
                    break;
                }
            }
            if (found) {
                result = min(result, score);
                if (result == score) {
                    best_way = way;
                }
            }
        }
    }
}
