#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits>
#include <stack>
#include <unordered_set>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<vector<pair<int, double>>> primMST(const vector<Point>& points) {
    int n = points.size();
    vector<bool> visited(n, false);
    vector<double> minEdge(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);
    vector<vector<pair<int, double>>> mst(n);

    minEdge[0] = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || minEdge[j] < minEdge[v])) {
                v = j;
            }
        }

        visited[v] = true;

        if (parent[v] != -1) {
            double w = distance(points[parent[v]], points[v]);
            mst[parent[v]].push_back({v, w});
            mst[v].push_back({parent[v], w});
        }

        for (int to = 0; to < n; to++) {
            double dist = distance(points[v], points[to]);
            if (!visited[to] && dist < minEdge[to]) {
                minEdge[to] = dist;
                parent[to] = v;
            }
        }
    }

    return mst;
}

vector<int> eulerTour(const vector<vector<pair<int, double>>>& mst) {
    vector<vector<int>> adjacency(mst.size());
    for (size_t i = 0; i < mst.size(); i++) {
        for (const auto& edge : mst[i]) {
            adjacency[i].push_back(edge.first);
        }
    }

    for (auto& adj : adjacency) {
        for (int neighbor : adj) {
            adjacency[neighbor].push_back(&adj - &adjacency[0]);
        }
    }

    for (auto& adj : adjacency) {
        sort(adj.begin(), adj.end());
        adj.erase(unique(adj.begin(), adj.end()), adj.end());
    }

    vector<int> tour;
    stack<int> st;
    st.push(0);

    while (!st.empty()) {
        int v = st.top();
        if (!adjacency[v].empty()) {
            int u = adjacency[v].back();
            adjacency[v].pop_back();
            adjacency[u].erase(find(adjacency[u].begin(), adjacency[u].end(), v));
            st.push(u);
        } else {
            tour.push_back(v);
            st.pop();
        }
    }

    return tour;
}

vector<int> shortcutTour(const vector<int>& eulerTour) {
    vector<int> hamiltonian;
    unordered_set<int> visited;

    for (int vertex : eulerTour) {
        if (visited.find(vertex) == visited.end()) {
            hamiltonian.push_back(vertex);
            visited.insert(vertex);
        }
    }
    hamiltonian.push_back(hamiltonian[0]);

    return hamiltonian;
}

double tourLength(const vector<int>& tour, const vector<Point>& points) {
    double length = 0.0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        length += distance(points[tour[i]], points[tour[i + 1]]);
    }
    return length;
}

vector<int> tspDoubleTree(const vector<Point>& points) {
    vector<vector<pair<int, double>>> mst = primMST(points);
    vector<int> euler = eulerTour(mst);
    vector<int> hamiltonian = shortcutTour(euler);
    return hamiltonian;
}
