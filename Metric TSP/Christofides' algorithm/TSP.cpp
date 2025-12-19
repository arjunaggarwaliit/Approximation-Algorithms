#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <stack>
#include <cmath>

class Christofides {
public:
    std::vector<std::vector<double>> distance;
    int n;
    std::vector<std::vector<int>> mstAdj;
    std::vector<int> oddVertices;
    std::vector<std::vector<int>> multiGraph;
    std::vector<int> eulerCircuit;
    std::vector<int> hamiltonianCycle;
    double tourLength;

    Christofides(const std::vector<std::vector<double>>& dist) {
        distance = dist;
        n = distance.size();
        mstAdj.resize(n);
        multiGraph.resize(n);
    }

    void findMST() {
        std::vector<double> key(n, std::numeric_limits<double>::max());
        std::vector<bool> inMST(n, false);
        std::vector<int> parent(n, -1);
        key[0] = 0.0;

        for (int i = 0; i < n - 1; ++i) {
            int u = -1;
            double minKey = std::numeric_limits<double>::max();
            for (int j = 0; j < n; ++j) {
                if (!inMST[j] && key[j] < minKey) {
                    minKey = key[j];
                    u = j;
                }
            }
            inMST[u] = true;
            for (int v = 0; v < n; ++v) {
                if (distance[u][v] > 0 && !inMST[v] && distance[u][v] < key[v]) {
                    key[v] = distance[u][v];
                    parent[v] = u;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (parent[i] != -1) {
                mstAdj[i].push_back(parent[i]);
                mstAdj[parent[i]].push_back(i);
                multiGraph[i].push_back(parent[i]);
                multiGraph[parent[i]].push_back(i);
            }
        }
    }

    void findOddVertices() {
        for (int i = 0; i < n; ++i) {
            if (mstAdj[i].size() % 2 == 1) {
                oddVertices.push_back(i);
            }
        }
    }

    void perfectMatching() {
        std::vector<bool> matched(n, false);
        for (size_t i = 0; i < oddVertices.size(); ++i) {
            if (matched[oddVertices[i]]) continue;
            int bestMatch = -1;
            double bestDist = std::numeric_limits<double>::max();
            for (size_t j = i + 1; j < oddVertices.size(); ++j) {
                if (matched[oddVertices[j]]) continue;
                double d = distance[oddVertices[i]][oddVertices[j]];
                if (d < bestDist) {
                    bestDist = d;
                    bestMatch = oddVertices[j];
                }
            }
            if (bestMatch != -1) {
                matched[oddVertices[i]] = true;
                matched[bestMatch] = true;
                multiGraph[oddVertices[i]].push_back(bestMatch);
                multiGraph[bestMatch].push_back(oddVertices[i]);
            }
        }
    }

    void eulerTour(int start) {
        std::vector<std::vector<int>> tempGraph = multiGraph;
        std::stack<int> stk;
        int pos = start;
        eulerCircuit.push_back(pos);
        while (!stk.empty() || !tempGraph[pos].empty()) {
            if (tempGraph[pos].empty()) {
                eulerCircuit.push_back(pos);
                pos = stk.top();
                stk.pop();
            } else {
                stk.push(pos);
                int neighbor = tempGraph[pos].back();
                tempGraph[pos].pop_back();
                auto it = std::find(tempGraph[neighbor].begin(), tempGraph[neighbor].end(), pos);
                if (it != tempGraph[neighbor].end()) {
                    tempGraph[neighbor].erase(it);
                }
                pos = neighbor;
            }
        }
        eulerCircuit.push_back(pos);
    }

    void shortcut() {
        std::vector<bool> visited(n, false);
        for (int v : eulerCircuit) {
            if (!visited[v]) {
                hamiltonianCycle.push_back(v);
                visited[v] = true;
            }
        }
        hamiltonianCycle.push_back(hamiltonianCycle[0]);
        tourLength = 0.0;
        for (size_t i = 0; i < hamiltonianCycle.size() - 1; ++i) {
            tourLength += distance[hamiltonianCycle[i]][hamiltonianCycle[i + 1]];
        }
    }

    void solve() {
        findMST();
        findOddVertices();
        perfectMatching();
        eulerTour(0);
        shortcut();
    }
};
