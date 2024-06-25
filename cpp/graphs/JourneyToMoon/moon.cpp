ing namespace std;
vector<vector<int>> adjList;
vector<bool> visited;
vector<int> CA;
int dfs(int s)
{
    stack<int> stk;
    stk.push(s);
    int nodeCount = 0;
    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();
        for (auto &u: adjList[node]) {
            if (visited[u]) continue;
            nodeCount += 1;
            visited[u] = 1;
            stk.push(u);
        }
    }
    return nodeCount;
}
int
main(void)
{
    int N, P;
    scanf("%d %d", &N, &P);
    adjList.resize(N);
    visited.resize(N, 0);
    for (int i = 0; i < P; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    int connected_component = 0;
    for (int i = 0; i < N; i++) {
        for (auto &u : adjList[i]) {
            if (!visited[u]) {
                visited[u] = 1;
                connected_component += 1;
                int count = dfs(u);
                CA.push_back(count+1);
            }
        }
    }
    for (int i = 0; i < N; i++)
        if (!visited[i]) CA.push_back(1);
    uint64_t  sum = 0;
    uint64_t result = 0;
    for(uint64_t size : CA)
    {
        result += sum*size;
        sum += size;
     }
    cout << result << "\n";
}
