#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, c[500][500];
struct edge {
    ll to, cap, rev;
    edge(ll x, ll y, ll z): to(x), cap(y), rev(z) {}
};
vector<edge> adj[500];
queue<int> q;

bool BFS(ll f[], pair<int, int> from[]) {
    int i = 0, u;
    fill(f + 1, f + n, 0);
    for (q.push(0); !q.empty(); q.pop()) {
        for (i = adj[u = q.front()].size(); i--;) {
            auto &e = adj[u][i];
            if (f[e.to] || e.cap <= 0) continue;
            from[e.to] = make_pair(u, i++);
            f[e.to] = min(f[u], e.cap);
            q.push(e.to);
        }
    }
    return f[n - 1] > 0;
}

ll EdmondsKarp() {
    int i, x, y;
    ll ans = 0, f[500]{LLONG_MAX};
    pair<int, int> from[500];
    while (BFS(f, from)) {
        for (x = n - 1; x; x = y) {
            y = from[x].first;
            i = from[x].second;
            adj[y][i].cap -= f[n - 1];
            adj[x][adj[y][i].rev].cap += f[n - 1];
        }
        ans += f[n - 1];
    }
    return ans;
}

int main() {
    // directed graph
    int i, j, u, v, w; cin >> n >> m;
    assert(n >= 1 && n <= 500);
    for (i = 0; i < m; i++) {
        cin >> u >> v >> w;
        assert(u >= 1 && u <= n);
        assert(v >= 1 && v <= n);
        assert(w >= 1 && w <= 1e9);
        c[--u][--v] += w;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (!c[i][j] && !c[j][i]) continue;
            u = adj[i].size(), v = adj[j].size();
            adj[i].emplace_back(j, c[i][j], v);
            adj[j].emplace_back(i, c[j][i], u);
        }
    }
    cout << EdmondsKarp() << '\n';
    return 0;
}