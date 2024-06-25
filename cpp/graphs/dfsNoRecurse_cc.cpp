#include <iostream>
#include <vector>
#include <stack>

using namespace std;
class Graph {
private:
    vector<int> *adjList;
    vector<bool> visited;
    int N; // nodes in graph;

public:
    Graph(int nodes) : N(nodes)
    {
        adjList = new vector<int> [nodes];
        visited.resize(nodes, 0);
    }
    ~Graph(void)
    {
        delete[] adjList;
        visited.clear();
    }
    void addNode(int u, int v)
    {
        adjList[u].push_back(v);
        if (u != v) adjList[v].push_back(u);
    }
    void dfs(int start)
    {
        stack<int> stk;
        stk.push(start);
        visited[start] = 1;
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            for (auto &v : adjList[u]) {
                if (visited[v]) continue;
                visited[v] = 1;
                stk.push(v);
            }
        }
    }
    int connectedComp(void)
    {
        int cc = 0;
        for (int i = 0; i < N; i++) {
            for (auto &u :  adjList[i]) {
                if (!visited[u]) {
                    dfs(u);
                    ++cc;
                }
            }
        }
        return cc;
    }
};

int main(void)
{
    Graph g(10);
    g.addNode(1, 3);
    g.addNode(1, 4);
    g.addNode(2, 5);
    g.addNode(7, 8);
    g.addNode(9, 6);
    cout << "cc = " << g.connectedComp() << "\n";
    return 0;
}
