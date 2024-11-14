//
// Created by Kuba on 23/10/2024.
//

#include "BFS.h"

//Z wektora A chcemy usunac wsyztskie wspolne wartości dla wektora B
void BFS::bfs(Node start, int size) {
    vector<pair<vector<Node* >, int>> ways = {
            { { &start }, 0 }
    };
    for(int x = 0; x < size-1; x++) {
        vector<pair<vector<Node *>, int>> newWays = vector<pair<vector<Node *>, int>>();
        for (pair<vector<Node *>, int> &p: ways) {
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

}