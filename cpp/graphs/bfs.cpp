#include <bits/stdc++.h>

using namespace std;

class Graph {
    private:
        vector<int> *adjList;
        int N;
        vector<bool> visited;
    public:
        Graph(int nodes)
        {
            N = nodes;
            adjList = new vector<int>[nodes];
            visited.resize(nodes, 0);
        }
        ~Graph(void)
        {
            delete[] adjList;
        }
        void addNode(int u, int v)
        {
            adjList[u].push_back(v);
        }
        void bfs(int s);
};

void Graph::bfs(int start)
{
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    cout << "Breadth First Traversal from Node-" << start << ":  ";
    while (!q.empty()) {
        int u = q.front();
        cout << u << ", ";
        q.pop();
        for (auto v: adjList[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

int main(void)
{
    Graph g(5);
    g.addNode(0, 1);
    g.addNode(0, 2);
    g.addNode(1, 2);
    g.addNode(2, 0);
    g.addNode(2, 3);
    g.addNode(3, 3);
 
    g.bfs(2);
    return 0;
}
