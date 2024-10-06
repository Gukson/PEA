#include <iostream>
#include "data/data_loader/DataLoader.h"
#include <vector>
#include "Tree/Node/Node.h"
#include "TSP/bruteForce/BruteForce.h"
using namespace std;



int main() {
    DataLoader dataLoader = DataLoader();
    vector<Node> nodes = dataLoader.loadData("tsp_10.txt");
    for (Node n: nodes ){
        cout << n.get_value() << " -> ";
        for(pair<Node*,int> p: n.getVectorOfNodes()){
            cout << p.first -> get_value() << ":" << p.second << ", ";
        }
        cout << endl;
    }

    BruteForce b = BruteForce();
    vector<int> visited = vector<int>();
    visited.push_back(0);
    b.bruteForce(nodes[0],0,visited,1,nodes.size());
    cout << "Best score: "<< b.result << endl;
    cout << "Best way: ";
    for(int x = 0 ; x < b.best_wat.size(); x++){
        cout << b.best_wat[x] << " ";
    }

    return 0;
}
