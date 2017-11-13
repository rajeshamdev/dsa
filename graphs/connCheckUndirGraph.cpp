#include <iostream>
#include <vector>

using namespace std;
class Graph {
    private:
        vector<int> *adjList;
        int numOfNodes;
        vector<bool> visited;

    public:
        Graph(int nodes) : numOfNodes(nodes)
        {
            adjList = new vector<int> [nodes];
            visited.resize(nodes, 0);
        }
        ~Graph(void) { delete[] adjList; }
        void dfs(const int &start)
        {
            if (visited[start]) return;
            visited[start] = 1;
            for (auto &u : adjList[start]) dfs(u);
        }
        void addNode(int u, int v)
        {
            adjList[u].push_back(v), adjList[v].push_back(u);
        }
        bool connCheck(void)
        {
            for (int i = 0; i < numOfNodes; i++)
                for (auto &u : adjList[i])
                    if (!visited[u]) return 0; 
            return 1;
        }
};

int
main(void)
{
    Graph g(10);
    g.addNode(1, 3);
    g.addNode(1, 4);
    //g.addNode(2, 5);
    g.dfs(4);
    cout << "Is this undirected graph connected: " << (g.connCheck() ? "YES" : "NO") << "\n";
    return 0;
}
