#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> intPair;
class Graph {
    private:
        vector<intPair> *adjList;
        int N;
        vector<bool> visited;
        vector<int> dist;
        const int INF = 1e9;
    public:
        Graph(int nodes)
        {
            N = nodes;
            adjList = new vector<intPair>[N+1];
            visited.resize(N+1, 0);
            dist.resize(N+1, INF);
        }
        ~Graph(void)
        {
            delete[] adjList;
        }
        void addNode(int u, int v, int w)
        {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
        void shortestDist(int s);
        void printDist(void);
};

void Graph::printDist(void)
{
    cout << "Node     Disttance\n";
    for (int i = 1; i <= N; i++) {
        cout << i << "    " << dist[i] << "\n";
    }
}

void Graph::shortestDist(int s)
{
    priority_queue<intPair, vector<intPair>, greater<intPair>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        for (auto adjNode : adjList[u]) {
            int v = adjNode.first;
            int w = adjNode.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main(void)
{
    Graph g(5);
    g.addNode(1, 2, 5);
    g.addNode(1, 4, 9);
    g.addNode(1, 5, 1);
    g.addNode(2, 1, 5);
    g.addNode(2, 3, 2);
    g.addNode(3, 2, 2);
    g.addNode(3, 4, 6);
    g.addNode(4, 3, 6);
    g.addNode(4, 1, 9);
    g.addNode(4, 5, 2);
    g.addNode(5, 1, 1);
    g.addNode(5, 4, 2);
    g.shortestDist(1);
    g.printDist();
    return 0;
}
