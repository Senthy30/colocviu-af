#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100100;

int N, M;
bool wasSeen[NMAX];
int v[NMAX], dp[NMAX];
vector <int> ans;
vector <int> edges[NMAX];

// explicatie
// ne folosim de algoritmul de sortare topologica
// vectorul dp ne arata daca nodul i mai are ramasa vreo muchie care n-a fost parcursa si intra in el
// daca vectorul dp este tot plin de zero,  atunci se pot parcurge toate cursurile, altfel nu

void read(int numCourses, const vector< vector <int> > &prerequisites){
    N = numCourses;
    for(auto v : prerequisites){
        int x = v[0];
        int y = v[1];
        edges[y].push_back(x);
        dp[x]++;
    }
}

void dfs(int node){
    wasSeen[node] = true;
    ans.push_back(node);
    for(auto it : edges[node])
        if(!wasSeen[it]){
            --dp[it];
            if(!dp[it]) dfs(it);
        }
}

vector<int> findOrder(int numCourses, const vector< vector <int> > &prerequisites) {
    read(numCourses, prerequisites);
    for(int i = 0; i < N; i++)
        if(!wasSeen[i] && !dp[i])
            dfs(i);
    bool isOk = true;
    for(int i = 0; i < N; i++)
        if(dp[i] > 0)
            isOk = false;

    if(isOk)
       return ans;
    else return {};
}

int main() {

    vector <int> v = findOrder(2, {{0,1}});
    for(auto element : v)
        cout << element << ' ';

    return 0;
}
