#include "RandomNeighbour.h"

void RandomNeighbour::randomNeighbour(vector<Node> nodes) {
    random_device rd;
    mt19937 g(rd());
    overTime = false;

    // Wektory permutacji
    vector<vector<int>> allPermutations;

    // Generowanie wszystkich permutacji
    vector<int> nodeValues;
    for (Node node : nodes) {
        nodeValues.push_back(node.get_value());
    }

    // Generowanie permutacji (w tym przypadku wszystkich permutacji bez powtórzeń)
    do {
        allPermutations.push_back(nodeValues);
    } while (next_permutation(nodeValues.begin(), nodeValues.end()));

    // Losowanie permutacji z dostępnych
    for (int x = 0; x < allPermutations.size(); x++) {
        if (allPermutations.empty()) {
            break;  // Jeżeli brak permutacji, zakończ
        }

        // Losowanie permutacji
        uniform_int_distribution<int> dist(0, allPermutations.size() - 1);
        int randIndex = dist(g);
        vector<int> perm = allPermutations[randIndex];

        // Usuń wybraną permutację z wektora
        allPermutations.erase(allPermutations.begin() + randIndex);

        // Obliczanie kosztu przejścia po wybranej permutacji
        int score = 0;
        vector<int> way;

        // Przechodzenie po permutacji
        for (int y = 0; y < perm.size() - 1; y++) {
            bool found = false;
            for (pair<Node*, int> p : nodes[y].getVectorOfNodes()) {
                if (p.first->get_value() == perm[y + 1]) {
                    score += p.second;
                    way.push_back(perm[y]);
                    found = true;
                    break;
                }

                // Sprawdzanie limitu czasu
                if (std::chrono::duration_cast<std::chrono::minutes>(
                        std::chrono::high_resolution_clock::now() - time).count() >= timeLimit) {
                    throw std::runtime_error("przekroczono limit czasowy");
                }
            }
            if (!found) {
                break;
            }
        }

        // Sprawdzenie kosztu dla pełnej permutacji
        if (way.size() == perm.size() - 1) {
            bool found = false;
            for (pair<Node*, int> p : nodes[nodes.size() - 1].getVectorOfNodes()) {
                if (p.first->get_value() == perm[0]) {
                    score += p.second;
                    way.push_back(perm[nodes.size() - 1]);
                    way.push_back(perm[0]);
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
