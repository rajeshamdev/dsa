#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int NOTVISITED = 1;
const int VISITING = 2;
const int VISITED = 3;

class DirectedGraph {
    private:
        vector<int> *adjList;
        vector<int> visited;
        int N; // num of nodes in graph.
        vector<int> tsortList; 
        bool dfs(const int &node)
        {
            if (visited[node] == VISITED) return 0;
            tsortList.push_back(node);
            if (visited[node] == VISITING) return 1; // cycle detected.
            visited[node] = VISITING;
            for (int &u : adjList[node]) {
                bool ret = dfs(u);
                if (ret == 1) return ret;
            }
            visited[node] = VISITED;
            return 0;
        }
    public:
        DirectedGraph(int nodes) : N(nodes)
        {
            adjList = new vector<int> [nodes+1];
            visited.resize(nodes+1, NOTVISITED);  
        }
        ~DirectedGraph(void)
        {
            delete[] adjList;
            visited.clear();
            tsortList.clear();
        }
        void addNode(const int &u, const int &v)
        {
            adjList[u].push_back(v);
        }
        bool topologicalSort(void)
        {
            for (int i = 1; i <= N; i++) {
                if (visited[i] == NOTVISITED) {
                    bool ret = dfs(i);
                    if (ret == 1) {
                        print();
                        tsortList.clear();
                        visited.clear();
                        visited.resize(N+1, NOTVISITED);
                    }
                }
            }
            return 0;
        }
        void print(void)
        {
            if (tsortList.empty()) return;
            cout << "Cycle: ";
            for (int &n : tsortList) {
                cout << n << " ";
            }
            cout << "\n";
        }
};

int main(void)
{
    int N, M; cin >> N >> M;
    DirectedGraph dg(N);
    while (M--) {
        int u, v; cin >> u >> v;
        dg.addNode(u, v);
    }
    cout << "\n" << dg.topologicalSort() << "\n";
}
