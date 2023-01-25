#include <bits/stdc++.h>
#define MAX 131072
#define fx first
#define fy second

using namespace std;
const int NMAX = 55;
const int KMAX = 1010;

struct edge{
    int x, time, watt;
};

FILE *IN, *OUT;

int N, M, K;
int Wmin, ans;
int dp[NMAX][KMAX];
bool charger[NMAX];

vector <edge> edges[NMAX];
queue <pair <int, int>> Q;

int pos, sign;
char f[MAX];

inline void Read(int &nr){
    sign = 0;
    nr = 0;
    while(f[pos] < '0' || f[pos] > '9'){
        if(f[pos] == '-') sign = 1;
        pos++;
        if(pos == MAX)
            fread(f, MAX, 1, IN), pos = 0;
    }
    while(f[pos] >= '0' && f[pos] <= '9'){
        nr = 10 * nr + f[pos++] - '0';
        if(pos == MAX)
            fread(f, MAX, 1, IN), pos = 0;
    }
    if(sign) nr =- nr;
}

void read(){
    int a;
    Read(N); Read(K);
    for(int i = 1; i <= N; i++)
        Read(a), charger[i] = a;
    Read(M);
    int b, t, c;
    for(int i = 1; i <= M; i++){
        Read(a); Read(b); Read(t); Read(c);
        edges[a].push_back({b, t, c});
        edges[b].push_back({a, t, c});
    }
}

inline int bellman_ford(int W){
    for(int i = 1; i <= N; i++)
        for(int j = 0; j <= K; j++)
            dp[i][j] = -1;
    Q.push({1, W});
    dp[1][W] = 0;
    while(!Q.empty()){
        pair <int, int> node = Q.front();
        if(charger[node.fx]){
            dp[node.fx][W] = dp[node.fx][node.fy];
            node.fy = W;
        }
        Q.pop();
        for(int i = 0; i < edges[node.fx].size(); i++){
            edge neigh = edges[node.fx][i];
            if(node.fy >= neigh.watt)
                if(dp[neigh.x][node.fy - neigh.watt] > dp[node.fx][node.fy] + neigh.time || dp[neigh.x][node.fy - neigh.watt] == -1){
                    dp[neigh.x][node.fy - neigh.watt] = dp[node.fx][node.fy] + neigh.time;
                    Q.push({neigh.x, node.fy - neigh.watt});
                }
        }
    }
    int tmin = 2e9;
    for(int i = 0; i <= W; i++)
        if(dp[N][i] != -1)
            tmin = min(tmin, dp[N][i]);
    return tmin;
}

int binsearch(int st, int dr){
    int mid, last = K;
    while(st <= dr){
        mid = (st + dr) / 2;
        if(bellman_ford(mid) == ans){
            dr = mid - 1;
            last = mid;
        } else st = mid + 1;
    }
    return last;
}

int main(){

    IN = fopen("lanterna.in", "r");
    OUT = fopen("lanterna.out", "w");

    read();
    ans = bellman_ford(K);
    Wmin = binsearch(0, K);
    fprintf(OUT, "%d %d", ans, Wmin);


    return 0;
}
