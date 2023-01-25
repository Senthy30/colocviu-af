#include <bits/stdc++.h>

using namespace std;
const int NMAX = 210;

int N, M, ansFlow, S, D;
bool wasSeen[NMAX];
int dad[NMAX];
int flow[NMAX][NMAX], capacity[NMAX][NMAX];
vector <int> edges[NMAX];

// cream un graf bipartit cu nodurile din input, si fiecare muchie citita, adaugam o muchie in graful nostru bipartit
// de la nodul din graful din stanga la nodul corespunzator la graful din dreapta
// tracem muchii de la S la nodurile din graful din stanga si muchii de la nodurile din graful din dreapta la D
// calculam fluxul aplicand algoritmul de flux maxim, iar la final raspunsul nostru va fi numarul total de noduri - fluxul maxim

void read(){
    scanf("%d%d", &N, &M);
    S = 0; D = 2 * N + 1;
    int x, y;
    for(int i = 1; i <= M; i++){
        scanf("%d%d", &x, &y);
        edges[x].push_back(N + y);
        edges[N + y].push_back(x);
        capacity[x][N + y] = 1;
    }

    for(int i = 1; i <= N; i++){
        edges[S].push_back(i);
        edges[i].push_back(S);
        capacity[S][i] = 1;

        edges[i].push_back(N + i);
        edges[N + i].push_back(i);
        capacity[N + i][i] = 1;

        edges[D].push_back(N + i);
        edges[N + i].push_back(D);
        capacity[N + i][D] = 1;
    }
}

bool generateFlow(int node){
    for(int i = 0; i <= D; i++){
        wasSeen[i] = false;
        dad[i] = 0;
    }
    queue <int> Q;
    Q.push(node);
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(auto it : edges[node]){
            if(!wasSeen[it] && capacity[node][it] - flow[node][it] > 0){
                wasSeen[it] = true;
                dad[it] = node;
                Q.push(it);
            }
        }
    }

    if(!dad[D])
        return false;

    node = D;
    for(auto it : edges[node]){
        if(capacity[it][node] - flow[it][node] > 0){
            int MinFlow = capacity[it][node] - flow[it][node];
            for(int j = it; j != S; j = dad[j])
                MinFlow = min(MinFlow, capacity[dad[j]][j] - flow[dad[j]][j]);
            flow[it][node] += MinFlow;
            flow[node][it] -= MinFlow;
            for(int j = it; j != S; j = dad[j]){
                flow[dad[j]][j] += MinFlow;
                flow[j][dad[j]] -= MinFlow;
            }
            ansFlow += MinFlow;
        }
    }
    return true;
}

int main() {

    freopen("drumuri2.in", "r", stdin);
    freopen("drumuri2.out", "w", stdout);

    read();

    bool repeat = true;
    while(repeat)
        repeat = generateFlow(0);
    printf("%d", N - ansFlow);

    return 0;
}
