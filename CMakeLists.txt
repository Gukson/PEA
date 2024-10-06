cmake_minimum_required(VERSION 3.28)
project(PEA)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA main.cpp
        TSP/random/RandomTSP.cpp
        TSP/random/RandomTSP.h
        Tree/Node/Node.cpp
        Tree/Node/Node.h
        TSP/bruteForce/BruteForce.cpp
        TSP/bruteForce/BruteForce.h
        TSP/bruteForce/BruteForce.h
        data/data_loader/DataLoader.cpp
        data/data_loader/DataLoader.h
        data/data_loader/DataLoader.h)
