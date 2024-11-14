#include "NearestNeighbour.h"

void NearestNeighbour::nearestNeighbour(Node start, int size, vector<Node*> visited) {
    int sum = 0;
    int count = 1;

    visited.push_back(&start);
    Node current_Node = start;
    while (count != size){
        vector<pair<Node*, int>> nodes = current_Node.getVectorOfNodes();
        usunWspolne(nodes,visited);

        std::sort(nodes.begin(), nodes.end(), [](const std::pair<Node*, int>& a, const std::pair<Node*, int>& b) {
            return a.second < b.second;
        });

        visited.push_back(nodes[0].first);
        sum += nodes[0].second;
        current_Node = *nodes[0].first;
        count += 1;
    }

    auto it = std::find_if(current_Node.getVectorOfNodes().begin(), current_Node.getVectorOfNodes().end(), [&start](const std::pair<Node*, int>& p) {
        return p.first->get_value() == start.get_value();  // Sprawdzamy, czy wartość w first.get_value() jest równa start.get_value()
    });

    if (it != current_Node.getVectorOfNodes().end()) {
        int index = std::distance(current_Node.getVectorOfNodes().begin(), it);
        visited.push_back(&start);
        sum += current_Node.getVectorOfNodes()[index].second;
        if(sum < result){
            result = sum;
            best_way.clear();
            for(Node* n: visited) best_way.push_back(n->get_value());
        }
    }
}

void NearestNeighbour::findBestWay(vector<Node> nodes) {
    vector<int> best_scores = vector<int>();
    vector<vector<int> > best_ways = vector<vector<int> >();
    for(int x = 0; x < nodes.size(); x++){
        vector<Node*> visited = vector<Node*>();
        nearestNeighbour(nodes[x], nodes.size(),visited);
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
