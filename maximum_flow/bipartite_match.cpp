#include <bits/stdc++.h>
using namespace std;

int n, m;
struct edge {
    int to, cap, cost, rev;
    edge(int a, int b, int c, int d): to(a), cap(b), cost(c), rev(d) {}
};
vector<edge> adj[500];
pair<int, int> from[500];
priority_queue<pair<int, int>> pq;

int dijkstra(int s, int t) {
    int i, u, w, dist[500];
    fill(dist, dist + t, 1e9);
    dist[s] = 0;
    for (pq.emplace(0, s); !pq.empty();) {
        tie(w, u) = pq.top(), pq.pop();
        if (w < dist[u]) continue;
        for (i = adj[u].size(); i--;) {
            auto &e = adj[u][i];
            if (dist[e.to] > dist[u] - e.cost) continue;
            dist[e.to] = dist[u] - e.cost;
            from[e.to] = make_pair(u, i);
            pq.emplace(dist[e.to], e.to);
        }
    }
    return (dist[n - 1] != 1e9)? -dist[n - 1]: -1;
}

int minCostMaxFlow(int s, int t) {
    int i, x, y, cost, ans = 0;
    while (cost = dijkstra(s, t)) {
        for (x = t; x != s; x = y) {
            tie(y, i) = from[i];
            adj[y][i].cap--;
            adj[x][adj[y][i].rev].cap++;
        }
        ans += cost;
    }
    return ans;
}

int main() {
    int i, u, v, w; cin >> n >> m;
    for (i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, 1, w, adj[v].size());
        adj[v].emplace_back(u, 0, -w, adj[u].size() - 1);
    }
    cout << minCostMaxFlow(0, n - 1) << '\n';
    return 0;
}