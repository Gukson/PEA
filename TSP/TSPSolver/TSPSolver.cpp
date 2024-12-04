//
// Created by Kuba on 07/10/2024.
//

#include "TSPSolver.h"

void TSPSolver::testAlgoritms(Config config) {
    outputFile.open("../data/output/" + config.outputFile, std::ios_base::app);

    b.timeLimit = config.maxTime;
    r.timeLimit = config.maxTime;
    d.timeLimit = config.maxTime;
    bfs.timeLimit = config.maxTime;
    l.timeLimit = config.maxTime;

    for (int index = 0; index < config.files.size(); index++) {
        outputFile << "Plik: " << config.files[index] << endl;

        //na początku trzeba zresetowac wszytskie zmienne
        b.result = INT_MAX;
        n.result = INT_MAX;
        r.result = INT_MAX;

        string p = config.files[index];

        int progressSave = 0;
        float progress = 0.0;
        DataLoader dataLoader = DataLoader();
        vector<Node> nodes = dataLoader.loadData(p);

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

        cout << "Wartośc rozwiązania optymalnego: " << dataLoader.optimum << endl;

        auto start = chrono::high_resolution_clock::now();
        auto finish = chrono::high_resolution_clock::now();

        if(config.bruteForce){
            timeMeasurements.clear();
            start = chrono::high_resolution_clock::now();
            finish = chrono::high_resolution_clock::now();
            cout << "BruteForce dla pliku " << p << " w trakcie liczenia" << endl;
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

                ms_double = finish - start;
                timeMeasurements.push_back(ms_double.count() / 1000);

                if (config.progressBar) {
                    progressBar(&progressSave, &progress, config.repetitionsPerInstance);
                }
                if (b.overTime) {
                    cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    break;
                }
            }
            cout << endl;

            statsOutput(calcStats(timeMeasurements),b.best_way,b.result,config.showInConsole, dataLoader.optimum);
        }

        if(config.nn){
            timeMeasurements.clear();
            cout << "NearestNeighbour dla pliku " << p << " w trakcie liczenia" << endl;
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
            statsOutput(calcStats(timeMeasurements),n.best_way,n.result,config.showInConsole, dataLoader.optimum);

        }

        if(config.radnom){
            timeMeasurements.clear();
            cout << "RandomNeighbour dla pliku " << p << " w trakcie liczenia" << endl;
            outputFile << "RandomNeighbour" << endl;
            r.optimum = dataLoader.optimum;
            progressSave = 0;
            progress = 0.0;
            for (int x = 0; x < config.repetitionsPerInstance; x++) {
                start = chrono::high_resolution_clock::now();
                r.time = start;
                try {
                    r.randomNeighbour(nodes);
                } catch (const std::runtime_error &e) {
                    std::cerr << "Błąd: " << e.what() << std::endl;
                    r.overTime = true;
                }
                finish = chrono::high_resolution_clock::now();

                ms_double = finish - start;
                timeMeasurements.push_back(ms_double.count() / 1000);

                if (config.progressBar) {
                    progressBar(&progressSave, &progress, config.repetitionsPerInstance);
                }
                if (r.overTime) {
                    cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    break;
                }
            }
            cout << endl;
            statsOutput(calcStats(timeMeasurements),r.best_way,r.result,config.showInConsole,dataLoader.optimum);
        }

        if(config.dfs){
            timeMeasurements.clear();
            progressSave = 0;
            progress = 0.0;
            start = chrono::high_resolution_clock::now();
            finish = chrono::high_resolution_clock::now();
            cout << "DFS " << p << " w trakcie liczenia" << endl;
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

                ms_double = finish - start;
                timeMeasurements.push_back(ms_double.count() / 1000);

                if (config.progressBar) {
                    progressBar(&progressSave, &progress, config.repetitionsPerInstance);
                }

                if (d.overTime) {
                    cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    break;
                }
            }
            cout << endl;

            statsOutput(calcStats(timeMeasurements),d.best_way,d.result,config.showInConsole,dataLoader.optimum);
        }

        if(config.bfs){
            timeMeasurements.clear();
            progressSave = 0;
            progress = 0.0;
            start = chrono::high_resolution_clock::now();
            finish = chrono::high_resolution_clock::now();
            cout << "BFS " << p << " w trakcie liczenia" << endl;
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

                ms_double = finish - start;
                timeMeasurements.push_back(ms_double.count() / 1000);

                if (config.progressBar) {
                    progressBar(&progressSave, &progress, config.repetitionsPerInstance);
                }
                if (bfs.overTime) {
                    cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    break;
                }
            }
            cout << endl;

            statsOutput(calcStats(timeMeasurements),bfs.best_way,bfs.result,config.showInConsole,dataLoader.optimum);

        }

        if(config.lcfs){
            timeMeasurements.clear();
            progressSave = 0;
            progress = 0.0;
            start = chrono::high_resolution_clock::now();
            finish = chrono::high_resolution_clock::now();
            cout << "LCFS " << p << " w trakcie liczenia" << endl;
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

                ms_double = finish - start;
                timeMeasurements.push_back(ms_double.count() / 1000);

                if (config.progressBar) {
                    progressBar(&progressSave, &progress, config.repetitionsPerInstance);
                }
                if (l.overTime) {
                    cout << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    outputFile << "Przekroczono limit " << config.maxTime << "minut!" << endl;
                    break;
                }
            }
            cout << endl;

            statsOutput(calcStats(timeMeasurements),l.best_way,l.result,config.showInConsole, dataLoader.optimum);
        }

        // Jeśli w Node masz wskaźniki, np. vector<Node*> children
        nodes.clear();          // Usuwa wszystkie elementy z wektora
        nodes.shrink_to_fit();  // Redukuje rozmiar alokowanej pamięci wektora do aktualnego rozmiaru


// Teraz możesz bezpiecznie wyczyścić vector
        nodes.clear();
        nodes.shrink_to_fit(); // Upewniamy się, że pamięć jest zwolniona


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

void TSPSolver::statsOutput(vector<double> stats, vector<int> best_way, int wynik, bool show, int bestWynik) {
    outputFile << "Średni czas;" << stats[0] << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] * 100 << "%" << endl;
    outputFile << "Średni błąd względny;" << stats[2] * 100 << "%" << endl;
    outputFile << endl;
    outputFile << "Uzyskano wynik: " << wynik << endl;

    outputFile << "Błąd względny wyniku: " << abs(wynik-bestWynik)/bestWynik << endl;

    outputFile << "Błąd bezwzględny wyniku: " << abs(wynik-bestWynik) << endl;

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

    if(show){
        cout << "Średni czas;" << stats[0] << endl;
        cout << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
        cout << "Średni błąd bezwzględny;" << stats[1] * 100 << "%" << endl;
        cout << "Średni błąd względny;" << stats[2] * 100 << "%" << endl;
        cout << endl;
        cout << "Uzyskano wynik: " << wynik << endl;
        cout << "Błąd względny wyniku: " << abs(wynik-bestWynik)/bestWynik << endl;
        cout << "Błąd bezwzględny wyniku: " << abs(wynik-bestWynik) << endl;
        cout << "Ścieżka z powyższym wynikiem: ";
        for (int x: best_way) {
            cout << x << " ";
        }
        cout << endl;
        cout << "LP czas blad bezwzgledny blad wzgledny" << endl;
        for (int x = 0; x < timeMeasurements.size(); x++) {
            cout << x + 1 << ";" << timeMeasurements[x] << ";" << absolutes[x] << ";" << relatives[x]
                 << endl;
        }
        cout << endl;
    }
}