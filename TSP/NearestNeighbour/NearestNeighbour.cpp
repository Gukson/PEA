//
// Created by Kuba on 06/10/2024.
//

#include "NearestNeighbour.h"

int NearestNeighbour::nearestNeighbour(Node start, int sum, vector<int> visited, int count, int size, int startNumb) {
    if(count == size && visited.size() == size){
//        for(int y = 0; y < visited.size(); y++) {
//            cout << visited[y] << " ";
//        }
        cout << endl;
        for(pair<Node*,int> p : start.getVectorOfNodes()){
            if(p.first -> get_value() == startNumb){
                result = min(sum + p.second, result);
                if(result == sum + p.second){
                    visited.push_back(startNumb);
                    best_way = visited;
                }
            }
        }
    }

    int min_cost = INT_MAX;
    //różnica w tej metodzie jest taka, że sortujemy wektor od najbliższego wierzchołka do najdalszej
    vector<pair<Node*, int>> nodes = start.getVectorOfNodes();
    std::sort(nodes.begin(), nodes.end(), [](std::pair<Node*, int>& a, std::pair<Node*, int>& b) {
        return a.second < b.second;  // Bezpośrednie porównanie int
    });
    for(pair<Node*,int> p : nodes){
        auto it = find(visited.begin(), visited.end(), p.first -> get_value());
        if(it == visited.end()){
            vector<int> w = vector<int>(visited);
            w.push_back(p.first -> get_value());
            int new_cost = nearestNeighbour(*p.first,sum+p.second,w,count+1,size, startNumb);
            min_cost = min(min_cost,new_cost);
        }
    }
}

void NearestNeighbour::findBestWay(vector<Node> nodes) {


    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    for(int x = 0; x < nodes.size(); x++){
        vector<int> visited = vector<int>();
        visited.push_back(x);
        nearestNeighbour(nodes[x],0,visited,1,nodes.size(),x);
        best_scores.push_back(result);
        best_ways.push_back(best_way);
        result = INT_MAX;
        best_way.clear();
        cout << x << endl;
    }
    auto min_it = std::min_element(best_scores.begin(), best_scores.end());
    cout << "Best score: "<< *min_it << endl;
    auto it = std::find(best_scores.begin(), best_scores.end(),*min_it);
    int index = distance(best_scores.begin(),it);

    cout << "Best way: ";
    for(int x : best_ways[index]){
        cout << x << " ";
    }
}
