//
// Created by Kuba on 07/10/2024.
//

#include "TSPSolver.h"

void TSPSolver::testAlgoritms(Config config) {
    ofstream outputFile("../data/output/" + config.outputFile, std::ios_base::app);

    for(int index = 0; index < config.files.size(); index++){
        outputFile << "Plik: " <<config.files[index].first << endl;

        //na początku trzeba zresetowac wszytskie zmienne
        b.result = INT_MAX;
        n.result = INT_MAX;
        r.result = INT_MAX;

        pair<string, int> p = config.files[index];
        bruteForceTime.push_back(vector<double>());
        nearTime.push_back(vector<double>());
        randomTime.push_back(vector<double>());

        int progressSave = 0;
        float progress = 0.0;
        DataLoader dataLoader = DataLoader();
        vector<Node> nodes = dataLoader.loadData(p.first);
        //czy wyświelić wierzchołki w konsoli
        if(config.showNodesInConsole){
            for (Node n: nodes ){
                cout << n.get_value() << " -> ";
                for(pair<Node*,int> p: n.getVectorOfNodes()){
                    cout << p.first -> get_value() << ":" << p.second << ", ";
                }
                cout << endl;
            }
        }

        //BruteForce
        auto start = chrono::high_resolution_clock::now();
        auto finish = chrono::high_resolution_clock::now();
        cout << "BruteForce dla pliku " << p.first << " w trakcie liczenia" << endl;
        for(int x = 0; x < config.repetitionsPerInstance; x++){
            start = chrono::high_resolution_clock::now();
            b.findBestWay(nodes);
            finish = chrono::high_resolution_clock::now();
            ms_double = finish - start;
            bruteForceTime[index].push_back(ms_double.count()/1000);

            if(config.progressBar){
                progressBar(&progressSave,&progress,config.repetitionsPerInstance);
            }
        }
        cout << endl;
        //wyliczyc sredni czas i odchylenie
        vector<double> stats = calcStats(bruteForceTime[index]);
        //wpisywanie do pliku
        outputFile << "BruteForce" << endl;
        outputFile << "Średni czas;" << stats[0] << endl;
        outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
        outputFile << "Średni błąd względny;" << stats[2]*100 << "%" << endl;
        outputFile << endl;
        outputFile << "LP;czas;blad bezwzgledny;blad wzgledny" << endl;
        for(int x = 0; x < bruteForceTime[index].size(); x++){
            outputFile << x + 1 << ";" << bruteForceTime[index][x] << ";" << absolutes[x] << ";" << relatives[x] << endl;
        }
        outputFile << endl;


        cout << "Średni czas: " << stats[0] << "s" << endl;
        cout << "Średni błąd bezwzględny: " << stats[1] << "s" << endl;
        cout << "Średni błąd względny: " << stats[2]*100 << "%" << endl;

        cout << "Uzyskano wynik: " << b.result << endl;
        if(nodes.size() < 16){
            cout << "Ścieżka z powyższym wynikiem: ";
            for(int x : b.best_way){
                cout << x << " ";
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;

        //NearestNeighbour
        cout << "NearestNeighbour dla pliku " << p.first << " w trakcie liczenia" << endl;
        progressSave = 0;
        progress = 0.0;
        for(int x = 0; x < config.repetitionsPerInstance; x++){
            start = chrono::high_resolution_clock::now();
            n.findBestWay(nodes);
            finish = chrono::high_resolution_clock::now();
            ms_double = finish - start;
            nearTime[index].push_back(ms_double.count()/1000);

            if(config.progressBar){
                progressBar(&progressSave,&progress,config.repetitionsPerInstance);
            }
        }
        cout << endl;
        stats = calcStats(nearTime[index]);
        //wpisywanie do pliku
        outputFile << "NearestNeighbour" << endl;
        outputFile << "Średni czas;" << stats[0] << endl;
        outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
        outputFile << "Średni błąd względny;" << stats[2]*100 << "%" << endl;
        outputFile << endl;
        outputFile << "LP;czas;blad bezwzgledny;blad wzgledny" << endl;
        for(int x = 0; x < nearTime[index].size(); x++){
            outputFile << x + 1 << ";" << nearTime[index][x] << ";" << absolutes[x] << ";" << relatives[x] << endl;
        }
        outputFile << endl;

        cout << "Średni czas: " << stats[0] << "s" << endl;
        cout << "Średni błąd bezwzględny: " << stats[1] << "s" << endl;
        cout << "Średni błąd względny: " << stats[2]*100 << "%" << endl;
        cout << "Uzyskano wynik: " << n.result << endl;
        if(nodes.size() < 16){
            cout << "Ścieżka z powyższym wynikiem: ";
            for(int x : n.best_way){
                cout << x << " ";
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;

        //RandomNeighbour
        cout << "RandomNeighbour dla pliku " << p.first << " w trakcie liczenia" << endl;
        long long permutacje = 1;
        for(int z = 1; z < nodes.size() + 1; z++){
            permutacje*=z;
        }
        permutacje = permutacje*config.percentOfRandomTest/100;

        progressSave = 0;
        progress = 0.0;
        for(int x = 0; x < config.repetitionsPerInstance; x++){
            start = chrono::high_resolution_clock::now();
            r.randomNeighbour(permutacje,nodes);
            finish = chrono::high_resolution_clock::now();
            ms_double = finish - start;
            randomTime[index].push_back(ms_double.count()/1000);

            if(config.progressBar){
                progressBar(&progressSave,&progress,config.repetitionsPerInstance);
            }
        }
        cout << endl;
        stats = calcStats(randomTime[index]);
        //wpisywanie do pliku
        outputFile << "RandomNeighbour" << endl;
        outputFile << "Średni czas;" << stats[0] << endl;
        outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
        outputFile << "Średni błąd względny;" << stats[2]*100 << "%" << endl;
        outputFile << endl;
        outputFile << "LP;czas;blad bezwzgledny;blad wzgledny" << endl;
        for(int x = 0; x < randomTime[index].size(); x++){
            outputFile << x + 1 << ";" << randomTime[index][x] << ";" << absolutes[x] << ";" << relatives[x] << endl;
        }
        outputFile << endl;
        cout << "Średni czas: " << stats[0] << "s" << endl;
        cout << "Średni błąd bezwzględny: " << stats[1] << "s" << endl;
        cout << "Średni błąd względny: " << stats[2]*100 << "%" << endl;
        cout << "wykonano " << permutacje << " losowań"<< endl;
        cout << "Uzyskano wynik: " << r.result << endl;
        if(nodes.size() < 16){
            cout << "Ścieżka z powyższym wynikiem: ";
            for(int x : r.best_way){
                cout << x << " ";
            }
        }

        cout << endl;
        cout << endl;
        cout << endl;
    }

}

void TSPSolver::progressBar(int* progressSave, float* progress, int repetitions) {
    *progress += float(100.0/repetitions);
    int barWidth = 70;
    if ((int)*progress - *progressSave > 0){
        *progressSave = (int)*progress;
        std::cout << "\r" <<"[";
        int pos = barWidth * *progress/100;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout <<  "=";
            else if (i == pos) std::cout << ">";
            else std::cout  << " ";
        }
        std::cout << "] " << int(*progress) << "%";
    }
    cout.flush();
}

vector<double> TSPSolver::calcStats(vector<double> time) {
    double avgTime;
    double sum = 0.0;
    for(double t: time){
        sum += t;
    }
    avgTime = sum / time.size();

    //liczenie błędu bezwzględnego

    //wektor absolut posiada błędy bezwzględne każdego z pomiarów
    vector<double> absolute = vector<double>();
    for(double t: time){
        absolute.push_back(abs(t - avgTime));
    }

    double avgAbsolute = 0.0;
    for(double t: absolute){
        avgAbsolute += t;
    }
    avgAbsolute =  avgAbsolute / absolute.size();

    //liczenie średniego błędu względnego

    //wektor relative posiada błędy względne każdego z pomiarów
    vector<double> relative = vector<double>();
    for(double t: time){
        relative.push_back(abs(t - avgTime)/avgTime);
    }

    double avgRelative = 0.0;
    for(double t: relative){
        avgRelative += t;
    }
    avgRelative =  avgRelative / absolute.size();

    vector<double> results = vector<double>();
    results.push_back(avgTime);
    results.push_back(avgAbsolute);
    results.push_back(avgRelative);

    absolutes = absolute;
    relatives = relative;

    return results;
}
