#include <bits/stdc++.h>

using namespace std;
const int N = 3000;
const int W = 1e5;
const int INF = 1e9;
typedef pair<int, int> intPair;
vector<intPair> graph[N];
bool visited[N];
int dist[N];

int
main(void)
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) graph[i].clear();
        for (int i = 0; i < m; i++) {
           int u, v, w;
           scanf("%d %d %d", &u, &v, &w);
           --u; --v;
           graph[u].push_back({v, w});
           graph[v].push_back({u, w});
        }
        int s;
        scanf("%d", &s);
        --s;
        fill(dist, dist+n, INF);
        fill(visited, visited+n, 0);
        dist[s] = 0;
        priority_queue<intPair, vector<intPair>, greater<intPair>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = 1;
            for (auto &neighbour: graph[u]) {
                int v = neighbour.first;
                int w = neighbour.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});        
                }
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(i == s) continue;
            printf("%d ", (dist[i] != INF ? dist[i] : -1));
        }
        printf("\n");
    }
}
