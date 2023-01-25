#include <bits/stdc++.h>
#define MAX 131072
#define INF 2100000000

using namespace std;
const int NMAX = 15100;

int T, N, M;
int seen[NMAX];
long long ans;
long long ssm[NMAX], val[NMAX];
vector <int> edges[NMAX];

void read(){
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++){
        scanf("%lld", &val[i]);
        ssm[i] = val[i];
        seen[i] = 0;
        edges[i].clear();
    }
    int a, b;
    for(int i = 1; i <= M; i++){
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        seen[b]++;
    }
    ans = -1e15;
}

void dfs(int node){
    seen[node]--;
    for(auto it : edges[node]){
        ssm[it] = max(ssm[it], ssm[node] + val[it]);
        seen[it]--;
        if(seen[it] == 0)
            dfs(it);
    }
}

int main(){

    freopen("easygraph.in", "r", stdin);
    freopen("easygraph.out", "w", stdout);

    scanf("%d", &T);
    for(int l = 1; l <= T; l++){
        read();
        for(int i = 1; i <= N; i++)
            if(seen[i] == 0)
                dfs(i);
        for(int i = 1; i <= N; i++)
            ans = max(ans, ssm[i]);
        printf("%lld\n", ans);
    }

    return 0;
}
