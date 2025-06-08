// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "train.h"

void saveData(const std::vector<int>& sizes, 
              const std::vector<int>& ops,
              const std::vector<double>& times,
              const std::string& filename) {
    std::ofstream out(filename);
    out << "n,operations,time\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << "," << ops[i] << "," << times[i] << "\n";
    }
}

void runExperiment(int n, bool light, std::vector<int>& ops, std::vector<double>& times) {
    Train train;
    for (int i = 0; i < n; i++) {
        train.addCar(light);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    int len = train.getLength();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    ops.push_back(train.getOpCount());
    times.push_back(duration.count());
}

void randomExperiment(int n, std::vector<int>& ops, std::vector<double>& times) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    
    Train train;
    for (int i = 0; i < n; i++) {
        train.addCar(distrib(gen));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    int len = train.getLength();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    ops.push_back(train.getOpCount());
    times.push_back(duration.count());
}

int main() {
    std::vector<int> sizes;
    std::vector<int> ops_all_off, ops_all_on, ops_random;
    std::vector<double> times_all_off, times_all_on, times_random;
    
    for (int n = 2; n <= 100; n += 2) {
        sizes.push_back(n);
        
        runExperiment(n, false, ops_all_off, times_all_off);
        runExperiment(n, true, ops_all_on, times_all_on);
        randomExperiment(n, ops_random, times_random);
    }
    
    saveData(sizes, ops_all_off, times_all_off, "result/experiment_all_off.csv");
    saveData(sizes, ops_all_on, times_all_on, "result/experiment_all_on.csv");
    saveData(sizes, ops_random, times_random, "result/experiment_random.csv");

    return 0;
}
