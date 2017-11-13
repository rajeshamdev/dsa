#include <iostream>
#include <vector>
#include <stack>

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
        bool isReachable(const int &u, const int &v) // using DFS algorith
        {
            stack<int> stk;
            visited[u] = 1;
            stk.push(u);
            while (!stk.empty()) {
                int n = stk.top();
                stk.pop();
                for (auto &m : adjList[n]) {
                    if (m == v) return 1;
                    if (!visited[m]) {
                        visited[m] = 1;
                        stk.push(m);
                    }
                }
            }
            return 0;
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
    int u, v;
    cin >> u >> v; // find if there is a path between (u, v).
    cout << g.isReachable(--u, --v) << "\n";
}
