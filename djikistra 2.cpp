#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

struct Edge {
    int to;
    int weight;
};

class Graph {
public:
    int numNodes;
    vector<vector<Edge>> adjList;

    Graph(int n) {
        numNodes = n;
        adjList.resize(n + 1); // 1-indexed nodes
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
    }
};

void dijkstra(const Graph& g, int startNode, vector<int>& dist, vector<int>& parent) {
    int n = g.numNodes;
    dist.assign(n + 1, INF);
    parent.assign(n + 1, -1);
    
    vector<bool> visited(n + 1, false);

   
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;


        for (const auto& edge : g.adjList[u]) {
            int v = edge.to;
            int weight = edge.weight;

       
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}


void printPath(int target, const vector<int>& parent) {
    if (target == -1) return;
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        cout << "N" << path[i];
        if (i > 0) cout << " -> ";
    }
}

int main() {
    Graph g(22);


    int edges[][3] = {
        {1,2,2}, {2,3,4}, {3,2,1}, {3,4,2}, {4,5,1}, {5,6,2}, {6,7,14}, {7,5,3},
        {6,8,5}, {8,9,3}, {8,15,15}, {9,10,2}, {9,8,7}, {10,11,2}, {11,12,10},
        {11,13,2}, {13,14,2}, {14,18,4}, {15,16,1}, {16,17,6}, {17,18,6},
        {18,19,4}, {19,20,3}, {20,21,2}, {21,22,20}, {22,20,3}
    };


    for (auto& e : edges) {
        g.addEdge(e[0], e[1], e[2]);
    }

    int startNode = 1;
    vector<int> dist;
    vector<int> parent;

    dijkstra(g, startNode, dist, parent);

    cout << "Node\tDistance\tPredecessor\n";
    cout << "---------------------------------\n";
    for (int i = 1; i <= g.numNodes; ++i) {
        cout << "N" << i << "\t";
        if (dist[i] == INF) cout << "INF\t\t";
        else cout << dist[i] << "\t\t";
        
        if (parent[i] == -1) cout << "-1\n";
        else cout << "N" << parent[i] << "\n";
    }


    int target = 22;
    cout << "\nShortest path from N" << startNode << " to N" << target << ":\n";
    printPath(target, parent);
    cout << "\nTotal cost: " << dist[target] << "\n";

    return 0;
}