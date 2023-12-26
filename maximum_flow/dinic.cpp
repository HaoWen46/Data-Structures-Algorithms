#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, lvl[1000], idx[1000];
struct edge {
    ll to, cap, rev;
    edge(ll a, ll b, ll c, ll d): to(a), cap(b), rev(c) {}
};
vector<edge> adj[1000];
queue<int> q;

bool BFS() {
    int u;
    fill(lvl + 1, lvl + n, -1);
    for (q.push(0); !q.empty(); q.pop()) {
        for (auto &e: adj[u = q.front()]) {
            if (~lvl[e.to] || e.cap <= 0) continue;
            lvl[e.to] = lvl[u] + 1;
            q.push(e.to);
        }
    }
    return lvl[n - 1] >= 0;
}

ll DFS(int u, ll f) {
    if (u == n - 1) return f;
    for (ll flow; ~idx[u]; idx[u]--) {
        auto &e = adj[u][idx[u]];
        if (lvl[e.to] != lvl[u] + 1 || e.cap <= 0) continue;
        if (!(flow = DFS(e.to, min(f, e.cap)))) continue;
        e.cap -= flow, adj[e.to][e.rev].cap += flow;
        return flow;
    }
    return 0;
}

ll dinic() {
    ll i, f, ans = 0;
    while (BFS()) {
        for (i = n; i--;) idx[i] = adj[i].size() - 1;
        while (f = DFS(0, f)) ans += f;
    }
    return ans;
}

int main() {
    // undirected graph
    int i, u, v, c, x, y; cin >> n >> m;
    assert(n > 1 && n <= 1000);
    for (i = 0; i < m; i++) {
        cin >> u >> v >> c;
        assert(u >= 0 && u < n);
        assert(v >= 0 && v < n);
        x = adj[u].size();
        y = adj[v].size();
        adj[u].emplace_back(v, c, y, 0);
        adj[v].emplace_back(u, c, x, 0);
    }
    cout << dinic() << '\n';
    return 0;
}