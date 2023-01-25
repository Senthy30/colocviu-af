#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 2010;
const int PRIMNRMAX = 300300;

int N, S, D;
bool wasSeen[NMAX], primeNr[PRIMNRMAX];
int v[NMAX], dad[NMAX];
int capacity[NMAX][NMAX], flow[NMAX][NMAX];
vector <int> ans;
vector <int> edges[NMAX];

// cream un graf bipatit in care nodurile din stanga reprezinta nodurile a caror valoare este para, iar pentru
// noduri din dreapta, nodurile a caror valoare este impara
// adauga muchii de la sursa la noduri din stanga, si de la nodurile din dreapta la destinatie de capacitate 1
// aplic flux pana cand nu mai pot obtine flux
// daca intr-un nod din stanga nu l-am putut vizita, il adaug in raspunsul, iar daca pentru un nod din dreapta
// l-am vizitat, il adaug in raspuns

void generateCiur(){
    for(int i = 1; i < PRIMNRMAX; i++)
        primeNr[i] = true;
    for(int i = 2; i < PRIMNRMAX; i++){
        if(!primeNr[i])
            continue;
        for(int j = 2 * i; j < PRIMNRMAX; j += i)
            primeNr[j] = false;
    }
}

void read(){
    scanf("%d", &N);
    S = 0; D = N + 1;
    for(int i = 1; i <= N; i++){
        scanf("%d", &v[i]);
        if(v[i] % 2){
            edges[i].push_back(D);
            edges[D].push_back(i);
            capacity[i][D] = 1;
        } else {
            edges[S].push_back(i);
            edges[i].push_back(S);
            capacity[S][i] = 1;
        }
    }
    for(int i = 1; i <= N; i++)
        for(int j = i + 1; j <= N; j++){
            if(primeNr[v[i] + v[j]]){
                edges[i].push_back(j);
                edges[j].push_back(i);
                if(v[i] % 2)
                    capacity[j][i] = 1;
                else capacity[i][j] = 1;
            }
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
    int flowValue = 0;
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
            flowValue += MinFlow;
        }
    }
    return (flowValue > 0);
}

int main(){

    freopen("cuplaj.in", "r", stdin);
    //freopen("cuplaj.out", "w", stdout);

    generateCiur();
    read();

    bool repeat = generateFlow(S);
    while(repeat){
        repeat = generateFlow(S);
    }
    for(int i = 1; i <= N; i++){
        if((v[i] % 2 == 0 && !wasSeen[i]) || (v[i] % 2 && wasSeen[i]))
            ans.push_back(v[i]);
    }

    printf("%d\n", ans.size());
    for(auto it : ans)
        printf("%d ", it);

    return 0;
}
