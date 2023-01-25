#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100010;

int N, M, Cx, Cy;
int dx[NMAX], dy[NMAX];
bool wasSeen[NMAX];

vector <int> edges[NMAX];

// explicatie
// aflam distanta catre fiecare nod relativ la Cx, respectiv Cy prin efectuarea unui BFS din aceste noduri
// afisam minimul pentru fiecare nod dintre aceste doua distante

void read(){
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    scanf("%d%d", &Cx, &Cy);
}

void resetWasSeen(){
    for(int i = 0; i <= N; i++)
        wasSeen[i] = false;
}

void BFS(int node, int d[]){
    queue <int> Q;
    Q.push(node);
    resetWasSeen();
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(auto it : edges[node]){
            if(!wasSeen[it]){
                Q.push(it);
                wasSeen[it] = true;
                d[it] = d[node] + 1;
            }
        }
    }
}

int main(){

    freopen("graf.in", "r", stdin);
    freopen("graf.out", "w", stdout);

    read();
    BFS(Cx, dx);
    BFS(Cy, dy);
    for(int i = 1; i <= N; i++){
        printf("%d ", min(dx[i], dy[i]));
    }

    return 0;
}
