//
// Created by Kuba on 07/10/2024.
//

#include "TSPSolver.h"

void TSPSolver::testAlgoritms(Config config) {
    outputFile.open("../data/output/" + config.outputFile, std::ios_base::app);

    for (int index = 0; index < config.files.size(); index++) {
        outputFile << "Plik: " << config.files[index].first << endl;

        //na początku trzeba zresetowac wszytskie zmienne
        b.result = INT_MAX;
        n.result = INT_MAX;
        r.result = INT_MAX;




        b.timeLimit = config.maxTime;
        r.timeLimit = config.maxTime;
        d.timeLimit = config.maxTime;
        bfs.timeLimit = config.maxTime;
        l.timeLimit = config.maxTime;


        pair<string, int> p = config.files[index];

        int progressSave = 0;
        float progress = 0.0;
        DataLoader dataLoader = DataLoader();
        vector<Node> nodes = dataLoader.loadData(p.first);
        //czy wyświelić wierzchołki w konsoli
        if (config.showNodesInConsole) {
            for (Node n: nodes) {
                cout << n.get_value() << " -> ";
                for (pair<Node *, int> p: n.getVectorOfNodes()) {
                    cout << p.first->get_value() << ":" << p.second << ", ";
                }
                cout << endl;
            }
        }


        timeMeasurements.clear();
        //BruteForce
        auto start = chrono::high_resolution_clock::now();
        auto finish = chrono::high_resolution_clock::now();
        cout << "BruteForce dla pliku " << p.first << " w trakcie liczenia" << endl;
        outputFile << "BruteForce" << endl;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            b.time = start;
            try {
                b.findBestWay(nodes);
            } catch (const std::runtime_error &e) {
                std::cerr << "Błąd: " << e.what() << std::endl;
                b.overTime = true;
            }
            finish = chrono::high_resolution_clock::now();
            if (b.overTime) {
                cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
            }
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;

        statsOutput(calcStats(timeMeasurements),b.best_way);

        timeMeasurements.clear();
        //NearestNeighbour
        cout << "NearestNeighbour dla pliku " << p.first << " w trakcie liczenia" << endl;
        outputFile << "NearestNeighbour" << endl;
        progressSave = 0;
        progress = 0.0;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            n.findBestWay(nodes);
            finish = chrono::high_resolution_clock::now();
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;
        statsOutput(calcStats(timeMeasurements),n.best_way);


        timeMeasurements.clear();
//      RandomNeighbour
        cout << "RandomNeighbour dla pliku " << p.first << " w trakcie liczenia" << endl;
        outputFile << "RandomNeighbour" << endl;
        long long permutacje = 1;
        for (int z = 1; z < nodes.size() + 1; z++) {
            permutacje *= z;
        }

        progressSave = 0;
        progress = 0.0;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            r.time = start;
            try {
                r.randomNeighbour(permutacje, nodes);
            } catch (const std::runtime_error &e) {
                std::cerr << "Błąd: " << e.what() << std::endl;
                r.overTime = true;
            }
            finish = chrono::high_resolution_clock::now();
            if (r.overTime) {
                cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
            }
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;
        statsOutput(calcStats(timeMeasurements),n.best_way);


        timeMeasurements.clear();
//      DFS
        start = chrono::high_resolution_clock::now();
        finish = chrono::high_resolution_clock::now();
        cout << "DFS " << p.first << " w trakcie liczenia" << endl;
        outputFile << "DFS" << endl;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            d.time = start;
            try {
                d.findBestWay(nodes);
            } catch (const std::runtime_error &e) {
                std::cerr << "Błąd: " << e.what() << std::endl;
                d.overTime = true;
            }
            finish = chrono::high_resolution_clock::now();
            if (d.overTime) {
                cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
            }
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;

        statsOutput(calcStats(timeMeasurements),d.best_way);


        timeMeasurements.clear();
//      BFS
        start = chrono::high_resolution_clock::now();
        finish = chrono::high_resolution_clock::now();
        cout << "BFS " << p.first << " w trakcie liczenia" << endl;
        outputFile << "BFS" << endl;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            bfs.time = start;
            try {
                bfs.findBestWay(nodes);
            } catch (const std::runtime_error &e) {
                std::cerr << "Błąd: " << e.what() << std::endl;
                bfs.overTime = true;
            }
            finish = chrono::high_resolution_clock::now();
            if (bfs.overTime) {
                cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
            }
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;

        statsOutput(calcStats(timeMeasurements),bfs.best_way);


        timeMeasurements.clear();
//      LCFS
        start = chrono::high_resolution_clock::now();
        finish = chrono::high_resolution_clock::now();
        cout << "LCFS " << p.first << " w trakcie liczenia" << endl;
        outputFile << "LCFS" << endl;
        for (int x = 0; x < config.repetitionsPerInstance; x++) {
            start = chrono::high_resolution_clock::now();
            l.time = start;
            try {
                l.findBestWay(nodes);
            } catch (const std::runtime_error &e) {
                std::cerr << "Błąd: " << e.what() << std::endl;
                l.overTime = true;
            }
            finish = chrono::high_resolution_clock::now();
            if (l.overTime) {
                cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
            }
            ms_double = finish - start;
            timeMeasurements.push_back(ms_double.count() / 1000);

            if (config.progressBar) {
                progressBar(&progressSave, &progress, config.repetitionsPerInstance);
            }
        }
        cout << endl;

        statsOutput(calcStats(timeMeasurements),l.best_way);
    }

}

void TSPSolver::progressBar(int *progressSave, float *progress, int repetitions) {
    *progress += float(100.0 / repetitions);
    int barWidth = 70;
    if ((int) *progress - *progressSave > 0) {
        *progressSave = (int) *progress;
        std::cout << "\r" << "[";
        int pos = barWidth * *progress / 100;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(*progress) << "%";
    }
    cout.flush();
}

vector<double> TSPSolver::calcStats(vector<double> time) {
    double avgTime;
    double sum = 0.0;
    for (double t: time) {
        sum += t;
    }
    avgTime = sum / time.size();

    //liczenie błędu bezwzględnego

    //wektor absolut posiada błędy bezwzględne każdego z pomiarów
    vector<double> absolute = vector<double>();
    for (double t: time) {
        absolute.push_back(abs(t - avgTime));
    }

    double avgAbsolute = 0.0;
    for (double t: absolute) {
        avgAbsolute += t;
    }
    avgAbsolute = avgAbsolute / absolute.size();

    //liczenie średniego błędu względnego

    //wektor relative posiada błędy względne każdego z pomiarów
    vector<double> relative = vector<double>();
    for (double t: time) {
        relative.push_back(abs(t - avgTime) / avgTime);
    }

    double avgRelative = 0.0;
    for (double t: relative) {
        avgRelative += t;
    }
    avgRelative = avgRelative / absolute.size();

    vector<double> results = vector<double>();
    results.push_back(avgTime);
    results.push_back(avgAbsolute);
    results.push_back(avgRelative);

    absolutes = absolute;
    relatives = relative;

    return results;
}

void TSPSolver::statsOutput(vector<double> stats, vector<int> best_way) {
    outputFile << "Średni czas;" << stats[0] << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] * 100 << "%" << endl;
    outputFile << "Średni błąd względny;" << stats[2] * 100 << "%" << endl;
    outputFile << endl;
    outputFile << "Uzyskano wynik: " << b.result << endl;
    outputFile << "Ścieżka z powyższym wynikiem: ";
    for (int x: best_way) {
        outputFile << x << " ";
    }
    outputFile << endl;
    outputFile << endl;
    outputFile << "LP;czas;blad bezwzgledny;blad wzgledny" << endl;
    for (int x = 0; x < timeMeasurements.size(); x++) {
        outputFile << x + 1 << ";" << timeMeasurements[x] << ";" << absolutes[x] << ";" << relatives[x]
                   << endl;
    }
    outputFile << endl;
}
