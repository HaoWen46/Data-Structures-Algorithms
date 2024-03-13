#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10000];
int root[16][10000], lev[10000];

void DFS(bool visited[], int u) {
    for (int v: adj[u]) {
        if (visited[v]) continue;
        lev[v] = lev[u] + 1;
        visited[v] = true;
        DFS(visited, v);
        root[0][v] = u;
    }
}

int LCA(int u, int v) {
    if (lev[u] < lev[v]) swap(u, v);
    for (int i = 13; i >= 0; i--) {
        if (lev[u] - lev[v] >= (1 << i)) u = root[i][u];
    }
    if (u == v) return u;
    for (int i = 13; i >= 0; i--) {
        if (root[i][u] != root[i][v]) continue;
        u = root[i][u], v = root[i][v];
    }
    return root[0][u];
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int i, j, n, m, q; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool visited[10000]{true};
    DFS(visited, 0);
    for (i = 1; i < 14; i++) {
        for (j = 0; j < n; j++) {
            root[i][j] = root[i - 1][root[i - 1][j]];
        }
    }
    for (cin >> q; q--;) {
        int u, v; cin >> u >> v;
        cout << LCA(u, v) << '\n';
    }
    return 0;
}