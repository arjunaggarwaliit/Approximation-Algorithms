#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    int V;
    vector<list<int>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vertexCoverApproximation() {
        vector<int> cover;
        vector<bool> visited(V, false);
        vector<list<int>> tempAdj = adj;

        for (int u = 0; u < V; u++) {
            if (!tempAdj[u].empty() && !visited[u]) {
                for (int v : tempAdj[u]) {
                    if (!visited[v]) {
                        cover.push_back(u);
                        cover.push_back(v);
                        visited[u] = true;
                        visited[v] = true;

                        for (int neighbor : tempAdj[u]) {
                            tempAdj[neighbor].remove(u);
                        }
                        tempAdj[u].clear();

                        for (int neighbor : tempAdj[v]) {
                            tempAdj[neighbor].remove(v);
                        }
                        tempAdj[v].clear();

                        break;
                    }
                }
            }
        }

        sort(cover.begin(), cover.end());
        cover.erase(unique(cover.begin(), cover.end()), cover.end());

        return cover;
    }

    vector<int> vertexCoverApproximation2() {
        vector<int> cover;
        vector<bool> inCover(V, false);

        vector<pair<int, int>> edges;
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                if (u < v) {
                    edges.push_back({u, v});
                }
            }
        }

        vector<bool> edgeCovered(edges.size(), false);

        while (true) {
            int edgeIndex = -1;
            for (int i = 0; i < edges.size(); i++) {
                if (!edgeCovered[i]) {
                    edgeIndex = i;
                    break;
                }
            }

            if (edgeIndex == -1) break;

            int u = edges[edgeIndex].first;
            int v = edges[edgeIndex].second;

            if (!inCover[u]) {
                cover.push_back(u);
                inCover[u] = true;
            }
            if (!inCover[v]) {
                cover.push_back(v);
                inCover[v] = true;
            }

            for (int i = 0; i < edges.size(); i++) {
                if (!edgeCovered[i]) {
                    int a = edges[i].first;
                    int b = edges[i].second;
                    if (a == u || a == v || b == u || b == v) {
                        edgeCovered[i] = true;
                    }
                }
            }
        }

        return cover;
    }

    int getVertices() const { return V; }

    int getEdges() const {
        int count = 0;
        for (int i = 0; i < V; i++) {
            count += adj[i].size();
        }
        return count / 2;
    }

    void printGraph() {
        cout << "Graph with " << V << " vertices and " << getEdges() << " edges:\n";
        for (int i = 0; i < V; i++) {
            if (!adj[i].empty()) {
                cout << i << ": ";
                for (int neighbor : adj[i]) {
                    if (neighbor > i) {
                        cout << "(" << i << "-" << neighbor << ") ";
                    }
                }
                cout << endl;
            }
        }
    }
};

