#include <bits/stdc++.h>

using namespace std;
const int EMAX = 1000010;
const int NMAX = 100010;

int N, M, nr;
bool visitedEdges[EMAX];
int degree[NMAX];
vector <pair <int, int>> edges[NMAX];
unordered_map <int, vector <int>> ans;

// calculez gradul pentru fiecare nod
// daca gradul unui nod este impar, atunci creez o muchie de la nodul S la node
// aplic un DFS iar conditia daca trec in urmatorul nod este daca am trecut sau nu prin muchia respectiva
// in timp ce aplic DFS creez raspunsul pentru problema

void dfs(int node){
    int nodeNeigh, edgeNeigh;
    while(!edges[node].empty()) {
        auto it = edges[node].back();
        nodeNeigh = it.first;
        edgeNeigh = it.second;

        edges[node].pop_back();

        if (visitedEdges[edgeNeigh] == false) {
            visitedEdges[edgeNeigh] = true;
            dfs(nodeNeigh);
        }
    }

    if (node == 0)
        nr++;
    else ans[nr].push_back(node);
}


int main() {
    freopen("cuplaj.in", "r", stdin);
    freopen("cuplaj.out", "w", stdout);

    scanf("%d%d", &N, &M);

    int x, y;
    for (int i = 0; i < M; i++){
        scanf("%d%d", &x, &y);

        edges[x].push_back({y, i});
        edges[y].push_back({x, i});

        degree[x] += 1;
        degree[y] += 1;
    }

    for (int node = 1; node <= N; node++)
        if (degree[node] % 2){
            edges[node].push_back({0, node + M});
            edges[0].push_back({node, node + M});
        }

    dfs(0);

    printf("%d\n", ans.size());
    for (auto vAns : ans){
        printf("%d ", vAns.second.size());
        for (auto it : vAns.second)
            printf("%d ", it);
        printf("\n");
    }

    return 0;
}
