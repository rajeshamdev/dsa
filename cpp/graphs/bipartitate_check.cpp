bool is_bipartite(vector< vector<int> > &graph)
{
    int n = graph.size();
    vector<int> side(n, 0);
    queue<int> q;
    side[0] = 1; // left
    q.push(0);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto &neighbour : graph[node]) {
            if (!side[neighbour]) {
                side[neighbour] = - side[node];
                q.push(neighbour); 
            } else if (side[neighbour] == side[node]) {
                return false; 
            }
        } 
    }
    return true; 
}
