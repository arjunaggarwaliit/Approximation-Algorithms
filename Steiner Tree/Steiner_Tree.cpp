#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Edge {
    int u, v;
    double weight;

    Edge(int u, int v, double w) : u(u), v(v), weight(w) {}
};

class Graph {
private:
    int V;
    vector<vector<pair<int, double>>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v, double weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    int size() const {
        return V;
    }

    const vector<vector<pair<int, double>>>& getAdj() const {
        return adj;
    }

    vector<double> dijkstra(int source) {
        vector<double> dist(V, numeric_limits<double>::max());
        priority_queue<pair<double, int>,
            vector<pair<double, int>>,
            greater<pair<double, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            double currentDist = top.first;
            int u = top.second;

            if (currentDist > dist[u]) continue;

            for (const auto& p : adj[u]) {
                int v = p.first;
                double w = p.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    vector<Edge> primMST(const vector<int>& terminals) {
        vector<bool> inMST(V, false);
        vector<double> key(V, numeric_limits<double>::max());
        vector<int> parent(V, -1);

        priority_queue<pair<double, int>,
            vector<pair<double, int>>,
            greater<pair<double, int>>> pq;

        int start = terminals[0];
        key[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            int u = top.second;

            if (inMST[u]) continue;
            inMST[u] = true;

            for (const auto& p : adj[u]) {
                int v = p.first;
                double w = p.second;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push({w, v});
                }
            }
        }

        vector<Edge> mst;
        for (int i = 0; i < V; i++) {
            if (parent[i] != -1)
                mst.emplace_back(parent[i], i, key[i]);
        }
        return mst;
    }
};

class SteinerTreeSolver {
private:
    Graph graph;
    vector<int> terminals;
    int graphSize;

    void dfs(int u, int parent,
             const vector<vector<pair<int,double>>>& treeAdj,
             vector<bool>& visited,
             vector<Edge>& result) {

        visited[u] = true;
        for (const auto& p : treeAdj[u]) {
            int v = p.first;
            double w = p.second;
            if (v != parent && !visited[v]) {
                result.emplace_back(u, v, w);
                dfs(v, u, treeAdj, visited, result);
            }
        }
    }

public:
    SteinerTreeSolver(const Graph& g, const vector<int>& t)
        : graph(g), terminals(t) {
        graphSize = graph.size();
    }

    vector<Edge> approximateSteinerTree() {
        int k = terminals.size();
        vector<vector<double>> dist(k, vector<double>(k));

        for (int i = 0; i < k; i++) {
            auto d = graph.dijkstra(terminals[i]);
            for (int j = 0; j < k; j++)
                dist[i][j] = d[terminals[j]];
        }

        Graph complete(k);
        for (int i = 0; i < k; i++)
            for (int j = i + 1; j < k; j++)
                complete.addEdge(i, j, dist[i][j]);

        return complete.primMST(vector<int>(k));
    }

    double calculateTreeWeight(const vector<Edge>& tree) {
        double sum = 0;
        for (auto& e : tree) sum += e.weight;
        return sum;
    }
};

vector<Edge> improveSteinerTree(const vector<Edge>& tree,
                               const Graph& graph,
                               const vector<int>& terminals) {

    vector<Edge> improved = tree;
    unordered_set<int> term(terminals.begin(), terminals.end());

    for (int v = 0; v < graph.size(); v++) {
        if (term.count(v)) continue;

        for (const auto& p : graph.getAdj()[v]) {
            int to = p.first;
            double w = p.second;
            improved.emplace_back(v, to, w);
        }
    }
    return improved;
}

int main() {
    int V, E;
    cin >> V >> E;

    Graph graph(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int K;
    cin >> K;
    vector<int> terminals(K);
    for (int i = 0; i < K; i++) cin >> terminals[i];

    SteinerTreeSolver solver(graph, terminals);

    auto tree = solver.approximateSteinerTree();
    auto improved = improveSteinerTree(tree, graph, terminals);

    cout << "Steiner Tree Edges:\n";
    for (auto& e : improved)
        cout << e.u << " " << e.v << " " << e.weight << "\n";

    cout << "Total Weight: "
         << solver.calculateTreeWeight(improved) << "\n";

    return 0;
}
