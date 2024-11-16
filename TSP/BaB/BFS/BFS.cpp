//
// Created by Kuba on 23/10/2024.
//

#include "BFS.h"

void BFS::bfs(Node start, int size) {

    vector<pair<vector<Node* >, int>> ways = {
            { { &start }, 0 }
    };
    for(int x = 0; x < size-1; x++) {
        vector<pair<vector<Node *>, int>> newWays = vector<pair<vector<Node *>, int>>();
        for (pair<vector<Node *>, int> &p: ways) {
            if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
                timeLimit) {
                throw std::runtime_error("przekroczono limit czasowy");
            }

            if(p.second >= result) continue;

            //temp -> lista wierzchołków do których można pójśc i chcemy z niego usunąc wszytskei wierzchołki już odwiedzone
            vector<pair<Node *, int>> temp = p.first[p.first.size() - 1]->getVectorOfNodes();
            usunWspolne(temp, p.first);

            //jeżeli wektor jest pusty to znaczy, że nie ma możliwości pójścia do kolejnego wierzchołka
            if (temp.empty()) {
                continue;
            }
            //dla każdego nowego mozlwiego wierzchołka tworzymy nową ścieżkę.
            //bierzemy kopię ścieżki p.first, dodajemy do niej nowy wierzchołek t.first
            for (pair<Node *, int> t: temp) {
                vector<Node *> n = p.first;
                n.push_back(t.first);
                newWays.push_back(make_pair(n, p.second + t.second));
            }
        }
        ways = newWays;
    }

    //dodajemy koszt ostatniego kroku jakim jest powrót do kroku początkowego i przy okazji eliminujemy ściezki, które okażą się nie posiadać cyklu hamiltona
    vector<pair<vector<Node *>, int>> newWays = vector<pair<vector<Node *>, int>>();
    for (pair<vector<Node *>, int> &p: ways){
        vector<pair<Node*,int>> temp = p.first[p.first.size()-1]->getVectorOfNodes();
        auto it = std::find_if(temp.begin(), temp.end(), [&start](pair<Node *, int> node) {
            return node.first->get_value() == start.get_value();
        });
        if(it != temp.end()){
            vector<Node *> n = p.first;
            n.push_back(&start);
            int index = std::distance(temp.begin(), it);
            newWays.push_back(make_pair(n,p.second+temp[index].second));
        }
    }
    ways = newWays;

    std::sort(ways.begin(), ways.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    result = ways[0].second;
    for(auto & x : ways[0].first){
        best_way.push_back(x->get_value());
    }

}

void BFS::findBestWay(vector<Node> nodes) {
    best_way.clear();
    overTime = false;
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    NearestNeighbour n = NearestNeighbour();
    for (int x = 0; x < nodes.size(); x++) {
        vector<Node*> visited2 = vector<Node*>();

        //liczenie NN jako ograniczenie górne
        n.nearestNeighbour(nodes[x],nodes.size(),visited2);
        result = n.result;

        bfs(nodes[x], nodes.size());

        //zapisywanie wyników
        best_scores.push_back(result);
        best_ways.push_back(best_way);

        //czyszczenie
        result = INT_MAX;
        best_way.clear();
    }
    auto min_it = std::min_element(best_scores.begin(), best_scores.end());
    result = *min_it;
    auto it = std::find(best_scores.begin(), best_scores.end(), *min_it);
    int index = distance(best_scores.begin(), it);
    best_way = best_ways[index];
}