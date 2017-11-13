#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    private:
        vector<int> *adjList;
        vector<bool> visited;
        int numOfNodes;

    public:
        Graph(int nodes) : numOfNodes(nodes)
        {
            adjList = new vector<int> [nodes];
            visited.resize(nodes, 0);
        }
        ~Graph(void) { delete[] adjList; }
        void addEdge(int u, int v)
        {
            adjList[u].push_back(v);
            if (v != u) adjList[v].push_back(u);
        }
        int countNodes(int startNode);
        int edgeCount(void);
};

int Graph::countNodes(int start)
{
    stack<int> stk;
    int nodeCount = 0;
    visited[start] = 1;
    stk.push(start), ++nodeCount;
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        for (auto &v : adjList[u]) {
            if (!visited[v]) visited[v] = 1, stk.push(v), ++nodeCount;
        }
    }
    return nodeCount;
}

int Graph::edgeCount(void)
{
    int sum = 0;
    for (int i = 0; i < numOfNodes; ++i) {
        sum += adjList[i].size();
    }
    return sum/2;
}

int
main(void)
{
    Graph g(6);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 2);
    g.addEdge(3, 5);
    g.addEdge(2, 5);
    g.addEdge(4, 3);
    int nodes = g.countNodes(1);
    int edges = g.edgeCount();
    cout << "nodes=" << nodes << ", edges=" << edges << "\n";
    if (edges != (nodes - 1))
        cout << "There is cycle in the graph\n";
    else cout << "There is no cycle in the graph\n";

    return 0;
}
