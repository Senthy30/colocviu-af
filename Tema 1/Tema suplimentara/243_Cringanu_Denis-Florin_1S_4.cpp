#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100;

bool existCycle;
int T, N, M;

bool wasSeen[NMAX];
vector <int> edges[NMAX];

// verificam daca graful dat are cicluri, daca are cicluri atunci nu exista nicio metoda de a-l prinde pe lesbulan
// daca graful dat nu are cicluri, inseamna ca graful dat devine un arbore
// taiem de 2 ori frunzele arborelui dupa care verificam gradul fiecarui nod, daca gradul unui nod este mai mare decat 2, atunci nu exista niciodata metoda de a-l prinde pe lesbulan
// in caz contrat, exista o metoda de a-l prinde pe lesbulan

void read(){
    existCycle = false;
    for(int i = 0; i < NMAX; i++){
        edges[i].clear();
        wasSeen[i] = false;
    }
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
}

void dfs(int node, int dad){
    wasSeen[node] = true;
    for(auto it : edges[node]){
        if(it != dad){
            if(wasSeen[it]) {
                existCycle = true;
                return;
            }
            dfs(it, node);
        }
    }
}

void removeLeafs(){
    vector <int> leafs;
    for(int i = 1; i <= N; i++)
        if(edges[i].size() == 1)
            leafs.push_back(i);
    for(auto node : leafs)
        if(edges[node].size()){
            int asc = edges[node][0];
            edges[asc].erase(find(edges[asc].begin(), edges[asc].end(), node));
            edges[node].pop_back();
        }
    leafs.clear();
}

bool solve(){
    for(int i = 1; i <= N; i++)
        if(!wasSeen[i])
            dfs(i, 0);
    if(existCycle)
        return false;
    removeLeafs();
    removeLeafs();
    for(int i = 1; i <= N; i++)
        if(edges[i].size() > 2)
            return false;
    return true;
}

int main(){

    freopen("lesbulan.in", "r", stdin);
    freopen("lesbulan.out", "w", stdout);

    scanf("%d", &T);
    while(T--){
        read();
        printf("%d\n", solve());
    }

    return 0;
}
