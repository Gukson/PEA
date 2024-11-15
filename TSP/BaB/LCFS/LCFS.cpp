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

                    if(result == optimum)break;
                }
            }
            pq.pop();
            continue;
        }

        for(auto &t: temp){
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

