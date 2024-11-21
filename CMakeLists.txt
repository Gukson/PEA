cmake_minimum_required(VERSION 3.28)
project(PEA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -W")

add_executable(PEA main.cpp
        Tree/Node/Node.cpp
        Tree/Node/Node.h
        TSP/bruteForce/BruteForce.cpp
        TSP/bruteForce/BruteForce.h
        TSP/bruteForce/BruteForce.h
        data/data_loader/DataLoader.cpp
        data/data_loader/DataLoader.h
        data/data_loader/DataLoader.h
        TSP/NearestNeighbour/NearestNeighbour.cpp
        TSP/NearestNeighbour/NearestNeighbour.h
        TSP/RandomNeighbour/RandomNeighbour.cpp
        TSP/RandomNeighbour/RandomNeighbour.h
        config/configClass/Config.cpp
        config/configClass/Config.h
        TSP/TSPSolver/TSPSolver.cpp
        TSP/TSPSolver/TSPSolver.h
        TSP/BaB/LCFS/LCFS.cpp
        TSP/BaB/DFS/DFS.cpp
        TSP/BaB/BFS/BFS.cpp
        TSP/pomocnicze/usunWspolne.cpp
        TSP/pomocnicze/usunWspolne.h)
