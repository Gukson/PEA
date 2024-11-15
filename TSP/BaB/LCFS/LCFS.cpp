//
// Created by Kuba on 06/11/2024.
//

#include "LCFS.h"

void LCFS::lcfs(Node start, int size) {
    priority_queue<Kolejkowicz> pq;
    pq.push({&start,0});

    while(true){
        if(pq.size() == 0) break;
        Kolejkowicz k = pq.top();

        //tworzymy kopię listy dostepnych wierzchołków;
        vector<pair<Node *, int>> temp = k.node->getVectorOfNodes();
        usunWspolne(temp,k.way);

        //jezeli nie można już nigdzie pójśc, to sprawdźmy czy możemy wrócić do wierzchołka początkowego
        if(temp.empty()){
            auto it = std::find_if(k.node->getVectorOfNodes().begin(), k.node->getVectorOfNodes().end(), [&start](pair<Node *, int> p) {
                return p.first->get_value() == start.get_value();
            });
            if(it != k.node->getVectorOfNodes().end()){

                int index = distance(k.node->getVectorOfNodes().begin(), it);
                if(k.cost + k.node->getVectorOfNodes()[index].second < result){
                    result = k.cost + k.node->getVectorOfNodes()[index].second;

                    best_way.clear();
                    for(int x = 0; x < k.way.size(); x++){
                        best_way.push_back(k.way[x]->get_value());
                    }
                }
            }
            pq.pop();
            continue;
        }

        for(auto &t: temp){
            if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
                timeLimit) {
                throw std::runtime_error("przekroczono limit czasowy");
            }

            vector<Node*> new_way = k.way;
            new_way.push_back(t.first);

            //jeżeli aktualny koszt przekrocyz bądź zrówna się z aktualnie najlepszy konsztem, to mozemy pominąć tą trasę wiedząc, że nie będzie na pewno najlepsza.
            if(k.cost + t.second >= result) continue;

            // Tworzymy nowy obiekt Kolejkowicz z aktualnym wierzchołkiem, nową ścieżką i zaktualizowanym kosztem
            Kolejkowicz u(t.first, new_way, k.cost + t.second);

            // Wrzucamy nowy obiekt do kolejki priorytetowej
            pq.push(u);
        }
        pq.pop();
    }

}

void LCFS::findBestWay(vector<Node> nodes) {
    overTime = false;
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    NearestNeighbour n = NearestNeighbour();
    for (int x = 0; x < nodes.size(); x++) {
        vector<Node*> visited2 = vector<Node*>();

        //liczenie NN jako ograniczenie górne
        n.nearestNeighbour(nodes[x],nodes.size(),visited2);
        result = n.result;

        lcfs(nodes[x], nodes.size());

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