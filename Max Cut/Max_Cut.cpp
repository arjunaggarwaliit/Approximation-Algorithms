#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <random>

class MaxCut {
private:
    int vertices;
    std::vector<std::vector<int>> adjacency;

public:
    MaxCut(int n) : vertices(n), adjacency(n) {}

    void addEdge(int u, int v) {
        adjacency[u].push_back(v);
        adjacency[v].push_back(u);
    }

    std::pair<std::vector<bool>, int> randomApproximation() {
        std::vector<bool> partition(vertices, false);
        std::srand(std::time(nullptr));

        for (int i = 0; i < vertices; ++i) {
            partition[i] = std::rand() % 2;
        }

        int cutSize = calculateCutSize(partition);
        return {partition, cutSize};
    }

    std::pair<std::vector<bool>, int> derandomizedApproximation() {
        std::vector<bool> partition(vertices, false);
        std::vector<int> score(vertices, 0);

        for (int v = 0; v < vertices; ++v) {
            int cutIfTrue = 0;
            int cutIfFalse = 0;

            for (int neighbor : adjacency[v]) {
                if (neighbor < v) {
                    if (partition[neighbor]) {
                        cutIfTrue++;
                    } else {
                        cutIfFalse++;
                    }
                }
            }

            partition[v] = (cutIfTrue >= cutIfFalse);
        }

        int cutSize = calculateCutSize(partition);
        return {partition, cutSize};
    }

    std::pair<std::vector<bool>, int> greedyApproximation() {
        std::vector<bool> partition(vertices, false);
        std::vector<int> difference(vertices, 0);
        std::vector<bool> inSet(vertices, false);

        for (int i = 0; i < vertices; ++i) {
            difference[i] = 0;
            for (int neighbor : adjacency[i]) {
                difference[i]++;
            }
        }

        auto cmp = [&](int a, int b) {
            return difference[a] < difference[b];
        };

        std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < vertices; ++i) {
            pq.push(i);
        }

        while (!pq.empty()) {
            int v = pq.top();
            pq.pop();

            if (inSet[v]) continue;

            partition[v] = true;
            inSet[v] = true;

            for (int neighbor : adjacency[v]) {
                if (!inSet[neighbor]) {
                    difference[neighbor]--;
                    pq.push(neighbor);
                }
            }
        }

        int cutSize = calculateCutSize(partition);
        return {partition, cutSize};
    }

    std::pair<std::vector<bool>, int> semiDefiniteRounding() {
        int iterations = 100;
        int bestCut = 0;
        std::vector<bool> bestPartition(vertices, false);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.0, 1.0);

        for (int iter = 0; iter < iterations; ++iter) {
            std::vector<double> randomVector(vertices);
            for (int i = 0; i < vertices; ++i) {
                randomVector[i] = dist(gen);
            }

            std::vector<bool> partition(vertices, false);
            for (int i = 0; i < vertices; ++i) {
                partition[i] = (randomVector[i] >= 0);
            }

            int currentCut = calculateCutSize(partition);
            if (currentCut > bestCut) {
                bestCut = currentCut;
                bestPartition = partition;
            }
        }

        return {bestPartition, bestCut};
    }

private:
    int calculateCutSize(const std::vector<bool>& partition) {
        int cutSize = 0;
        for (int u = 0; u < vertices; ++u) {
            for (int v : adjacency[u]) {
                if (u < v && partition[u] != partition[v]) {
                    cutSize++;
                }
            }
        }
        return cutSize;
    }
};
