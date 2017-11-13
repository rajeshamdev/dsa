#include <bits/stdc++.h>
using namespace std;
class graph {
    public:
        int totalNodes;
        graph(int n);
        void addNode(int u, int v) {
            adjList[u].push_back(v), adjList[v].push_back(u);
        }
        uint64_t pickAstronauts(void);
        int connectedComponets(void);
    private:
        vector<bool> visited;
        vector<vector<int>> adjList;
        int dfs(int startNode);
        vector<int> astronautsInCountry;
};

graph::graph(int nodes)
{   
    totalNodes = nodes;
    visited.resize(totalNodes, 0); // bool visited[totalNodes];
    adjList.resize(totalNodes); // vector<int> adjList[totalNodes];
}

int
graph::dfs(int startNode)
{   
    int numOfEdges = 0;
    stack<int> stk;
    stk.push(startNode);
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();
        for (auto &u : adjList[node]) {
            if (visited[u]) continue;
            visited[u] = 1;
            ++numOfEdges;
            stk.push(u);
        }
    }
    return numOfEdges;
}

int
graph::connectedComponets(void)
{
    int cc = 0;
    for (int i = 0; i < totalNodes; i++) {
        for (auto &u : adjList[i]) {
            if (!visited[u]) {
                visited[u] = 1;
                cc += 1;
                int edgesCount = dfs(u);
                astronautsInCountry.push_back(edgesCount+1);
            }
        }
    }
    for (int i = 0; i < totalNodes; i++)
        if (!visited[i]) astronautsInCountry.push_back(1);
    return cc;
}

uint64_t
graph::pickAstronauts(void)
{
    uint64_t  sum = 0;
    uint64_t result = 0;
    for(uint64_t size : astronautsInCountry)
    {
        result += sum*size;
        sum += size;
     }
    return result;
}

int
main(void)
{
    int N, P;
    scanf("%d %d", &N, &P);
    graph g(N);
    for (int i = 0; i < P; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g.addNode(u, v);
    }
    int cc = g.connectedComponets();
    uint64_t selectionWays = g.pickAstronauts();
    cout << selectionWays << "\n";
}
