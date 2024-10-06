//
// Created by Kuba on 04/10/2024.
//

#include "BruteForce.h"

int BruteForce::bruteForce(Node start,int sum, vector<int> visited,int count, int size) {
    if(count == size && visited.size() == size){
        for(pair<Node*,int> p : start.getVectorOfNodes()){
            if(p.first -> get_value() == 0){
                result = min(sum + p.second, result);
                if(result == sum + p.second){
                    visited.push_back(0);
                    best_wat = visited;
                }
            }
        }
    }

    int min_cost = INT_MAX;

    for(pair<Node*,int> p : start.getVectorOfNodes()){
        auto it = find(visited.begin(), visited.end(), p.first -> get_value());
        if(it == visited.end()){
            vector<int> w = vector<int>(visited);
            w.push_back(p.first -> get_value());
            int new_cost = bruteForce(*p.first,sum+p.second,w,count+1,size);
            min_cost = min(min_cost,new_cost);
        }
    }


    return min_cost;
}