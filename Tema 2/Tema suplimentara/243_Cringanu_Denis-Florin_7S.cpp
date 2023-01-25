#include <bits/stdc++.h>

using namespace std;

struct obj2{
    int x, cost;
};

struct obj3{
    int x, y, cost;
};

int N, M;
int bell[105][105];
vector <obj2> edges[105];

void read(int n, vector<vector<int>>& flights){
    N = n;
    for(auto it : flights) {
        edges[it[0]].push_back({it[1], it[2]});
        ++M;
    }
    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
            bell[i][j] = 2e9;
}

void bellmanford(obj3 pos){
    queue <obj3> Q;
    bell[pos.y][pos.x] = pos.cost;
    Q.push(pos);
    while(!Q.empty()){
        pos = Q.front();
        Q.pop();
        for(auto it : edges[pos.x]){
            if(bell[pos.y + 1][it.x] > it.cost + bell[pos.y][pos.x]){
                bell[pos.y + 1][it.x] = it.cost + bell[pos.y][pos.x];
                Q.push({it.x, pos.y + 1, it.cost + bell[pos.y][pos.x]});
            }
        }
    }
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    read(n, flights);
    bellmanford({src, 0, 0});

    int ans = 2e9;
    for(int i = 1; i <= k + 1; i++)
        ans = min(ans, bell[i][dst]);

    if(ans == 2e9)
        return -1;
    return ans;
}

int main() {

    vector< vector<int> > edgeList = {{0,1,100},{1,2,100},{0,2,500}};
    vector< vector<int> > queries = {{0,4,14},{1,4,13}};

    int ans = findCheapestPrice(3, edgeList, 0, 2, 0);

    cout << ans;

}
