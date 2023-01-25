#include <bits/stdc++.h>

using namespace std;
const int NMAX = 1010;

struct obj {
    int x, y, cost;
};

int N, M;
int comp[1010];
vector <obj> edges;

void read(const vector<vector<int>>& points){
    N = points.size();
    for(int i = 0; i < N; i++){
        pair <int, int> x = {points[i][0], points[i][1]};
        for(int j = i + 1; j < N; j++){
            pair <int, int> y = {points[j][0], points[j][1]};
            edges.push_back({i + 1, j + 1, abs(x.first - y.first) + abs(x.second - y.second)});
            ++M;
        }
    }
    for(int i = 1; i <= N; i++)
        comp[i] = i;
}

inline int Find(int x){
    int root = x, aux;
    while(root != comp[root])
        root = comp[root];
    while(x != root){
        aux = comp[x];
        comp[x] = root;
        x = aux;
    }
    return x;
}

inline void Union(int x, int y){
    comp[x] = y;
}

bool cmp(obj a, obj b){
    return a.cost < b.cost;
}

int minCostConnectPoints(const vector<vector<int>>& points) {
    read(points);
    sort(edges.begin(), edges.end(), cmp);

    int x, y, totalCost = 0;
    for(int i = 0; i < M; i++){
        x = Find(edges[i].x);
        y = Find(edges[i].y);
        if(x != y){
            printf("%d %d %d\n", edges[i].x, edges[i].y, edges[i].cost);
            Union(x, y);
            totalCost += edges[i].cost;
        }
    }

    return totalCost;
}

int main() {

    cout << minCostConnectPoints({{0,0},{2,2},{3,10},{5,2},{7,0}});

}
