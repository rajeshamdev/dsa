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
            adjList = new vector<int> [nodes], visited.resize(nodes, 0);
        }
        ~Graph(void) { delete[] adjList; }
        void addNode(int u, int v)
        {
            adjList[u].push_back(v), adjList[v].push_back(u);
          
        }
        bool dfs(int start);
};

bool Graph::dfs(int startNode)
{
    stack<int> stk;
    stk.push(startNode);
    while(!stk.empty()) {
        int u = stk.top();
        stk.pop();
        if (visited[u]) return 1;
        visited[u] = 1;
        for (auto &v : adjList[u])
            if (!visited[v]) stk.push(v);
    }
    return 0;
}

int
main(void)
{
    Graph g1(3);
    g1.addNode(0, 1);
    g1.addNode(1, 2);
    g1.dfs(2) ? cout << "Graph contains cycle\n":
                   cout << "Graph doesn't contain cycle\n";

    Graph g2(6);
    g2.addNode(1, 3);
    g2.addNode(1, 4);
    g2.addNode(3, 2);
    g2.addNode(3, 5);
    g2.addNode(2, 5);
    g2.dfs(1) ? cout << "Graph contains cycle\n":
                   cout << "Graph doesn't contain cycle\n";
    return 0;
}
