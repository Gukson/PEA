//
// Created by Kuba on 06/10/2024.
//

#include "NearestNeighbour.h"

void NearestNeighbour::nearestNeighbour(Node start, int size) {
    int sum = 0;
    int count = 1;
    vector<int> visited = vector<int>();
    visited.push_back(start.get_value());
    Node current_Node = start;
    while (count != size){
        vector<pair<Node*, int>> nodes = current_Node.getVectorOfNodes();
        std::sort(nodes.begin(), nodes.end(), [](std::pair<Node*, int>& a, std::pair<Node*, int>& b) {
            return a.second < b.second;  // Bezpośrednie porównanie int
        });
        int index = 0;
        while(true){
            int currval = nodes[index].first -> get_value();
            auto it = find(visited.begin(),visited.end(),currval);
            if(it == visited.end()){
                break;
            } else{
                index++;
            }
        }
        visited.push_back(nodes[index].first->get_value());
        sum += nodes[index].second;
        current_Node = *nodes[index].first;
        count += 1;
    }
    for(pair<Node*,int> p : current_Node.getVectorOfNodes()){
        if(p.first -> get_value() == start.get_value()){
            result = min(sum + p.second, result);
            if(result == sum + p.second){
                visited.push_back(start.get_value());
                best_way = visited;
            }
        }
    }
}

void NearestNeighbour::findBestWay(vector<Node> nodes) {
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    for(int x = 0; x < nodes.size(); x++){
        vector<int> visited = vector<int>();
        visited.push_back(x);
        nearestNeighbour(nodes[x],nodes.size());
        best_scores.push_back(result);
        best_ways.push_back(best_way);
        result = INT_MAX;
        best_way.clear();
    }
    auto min_it = std::min_element(best_scores.begin(), best_scores.end());
    result = *min_it;
    auto it = std::find(best_scores.begin(), best_scores.end(),*min_it);
    int index = distance(best_scores.begin(),it);
    best_way = best_ways[index];
}
