#include <iostream>
#include "data/data_loader/DataLoader.h"
#include <vector>
#include "Tree/Node/Node.h"
#include "TSP/bruteForce/BruteForce.h"
#include "TSP/NearestNeighbour/NearestNeighbour.h"
#include "TSP/RandomNeighbour/RandomNeighbour.h"
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

//    BruteForce b = BruteForce();
//    b.findBestWay(nodes);

//    NearestNeighbour n = NearestNeighbour();
//    n.findBestWay(nodes);

    RandomNeighbour r = RandomNeighbour();
    r.randomNeighbour(10000,nodes);

    return 0;
}
