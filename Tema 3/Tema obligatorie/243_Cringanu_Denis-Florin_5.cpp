#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 11;
const int DIMMASK = (1 << NMAX);

int N;
int dp[NMAX][DIMMASK + 5];
vector <int> edges[NMAX];

// calculam distanta minima folosindu-ne de o dinamica pe masti
// dp[node][mask] = distantina minima ca sa ajungem in nodul node, daca am trecut prin toate nodurile unde mask are bitul 1

int shortestPathLength(const vector<vector<int>>& graph) {
    int nodeC = 0;
    for(auto v : graph){
        for(auto it : v){
            edges[nodeC].push_back(it);
        }
        ++nodeC;
    }
    N = graph.size();

    for(int node = 0; node < N; node++){
        for(int mask = 0; mask < (1 << N); mask++)
            dp[node][mask] = 2e9;
        dp[node][1 << node] = 0;
    }

    for(int mask = 1; mask < (1 << N); mask++){
        for(int node = 0; node < N; node++){
            if(!(mask & (1 << node)))
                continue;
            for(auto it : edges[node])
                dp[node][mask] = min(dp[node][mask], min(dp[it][mask ^ (1 << node)], dp[it][mask]) + 1);
        }
        for(int node = 0; node < N; node++){
            if(!(mask & (1 << node)))
                continue;
            for(auto it : edges[node])
                dp[node][mask] = min(dp[node][mask], min(dp[it][mask ^ (1 << node)], dp[it][mask]) + 1);
        }
    }
    int ans = 2e9;
    for(int node = 0; node < N; node++)
        ans = min(ans, dp[node][(1 << N) - 1]);

    return ans;
}

int main(){

    int ans = shortestPathLength({{1,2,3},{0},{0},{0}});
    cout << ans;

    return 0;
}
