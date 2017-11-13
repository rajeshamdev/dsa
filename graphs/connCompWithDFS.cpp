#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    private:
        vector<int> *adjList;
        vector<int> visited;
        int N; // num of nodes in graphs.
    public:
        Graph(int nodes) : N(nodes)
        {
            adjList = new vector<int> [nodes];
            visited.resize(nodes, 0);
        }
        ~Graph(void)
        {
            delete[] adjList; visited.clear();
        }
        void addNode(const int &u, const int &v)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
            
        }
        void bfs(const int &u)
        {
            queue<int> q;
            q.push(u);
            visited[u] = 1;
            while(!q.empty()) {
                int n = q.front();
                q.pop();
                for (auto &v : adjList[n]) {
                    if (visited[v]) continue;
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
        int connComp(void)
        {
            int cc = 0;
            for (int i = 0; i < N; i++) {
                for (auto &u : adjList[i]) {
                    if (visited[u]) continue;
                    bfs(u); ++cc;
                }
            }
            // count each unvisited node.
            for (int i = 0; i < N; i++) {
                if (!visited[i]) ++cc;
            }
            return cc;
        }
};

int main(void)
{
    int n, m;
    cin >> n >> m; // n is num of nodes and m is num of edges.
    Graph g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g.addNode(u, v);
    }
    cout << g.connComp() << "\n";
}
