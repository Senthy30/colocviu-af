#include <bits/stdc++.h>

using namespace std;
const int NMAX = 1010;

int N, M, ansFlow;
bool wasSeen[NMAX];
int dad[NMAX];
int flow[NMAX][NMAX], capacity[NMAX][NMAX];
vector <int> edges[NMAX], directedEdges[NMAX];

void read(){
    scanf("%d%d", &N, &M);
    int x, y, c;
    for(int i = 1; i <= M; i++){
        scanf("%d%d%d", &x, &y, &c);
        directedEdges[x].push_back(y);
        edges[x].push_back(y);
        edges[y].push_back(x);
        capacity[x][y] = c;
    }
}

// rezolvare cerinta b
// aplic un BFS pe garful citit (orientat) si verific daca mai pot trimite flux pe o muchie intre 2 noduri
// pornesc din nodul 1 si aplic BFS, daca pe o muchie capacitate de flux este maxim, atunci adaug muchia intr-un vector,
// la final verific daca am putut ajunge in nodul N, iar daca nu, afisez taietura minima

void printMinimumCut(int node){
    for(int i = 1; i <= N; i++)
        wasSeen[i] = false;
    bool canBeReached = false;
    vector <pair <int, int> > cutEdges;
    queue <int> Q;
    Q.push(node);
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        if(node == N)
            canBeReached = true;
        Q.pop();
        for(auto it : directedEdges[node]){
            if(capacity[node][it] - flow[node][it] == 0){
                cutEdges.push_back(make_pair(node, it));
                continue;
            }
            if(!wasSeen[it]) {
                wasSeen[it] = true;
                Q.push(it);
            }
        }
    }
    if(!canBeReached){
        printf("Taietura minima la momentul de fata este intre muchiile:\n");
        for(auto it : cutEdges)
            printf("%d %d\n", it.first, it.second);
        printf("Si are costul: %d\n", ansFlow);
    }
}

// rezolvare cerinta a
// aplic algoritmul de flux, pornesc un BFS din nodul 1 si incerc sa ajung in nodul N pe muchiile care inca nu
// si-au atins capacitatea maxima, iar pentru fiecare nod retin nodul de unde am venit
// pentru toti vecinii lui N, calculez fluxul cu care pot sa ajung intr-un vecin de a lui, uitandu-ma la tatii acestuia
// insumez toate fluxurile gasite si obtin rezultatul

bool generateFlow(int node){
    for(int i = 1; i <= N; i++){
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

    if(!dad[N])
        return false;

    node = N;
    for(auto it : edges[node]){
        if(capacity[it][node] - flow[it][node] > 0){
            int MinFlow = capacity[it][node] - flow[it][node];
            for(int j = it; j != 1; j = dad[j])
                MinFlow = min(MinFlow, capacity[dad[j]][j] - flow[dad[j]][j]);
            flow[it][node] += MinFlow;
            flow[node][it] -= MinFlow;
            for(int j = it; j != 1; j = dad[j]){
                flow[dad[j]][j] += MinFlow;
                flow[j][dad[j]] -= MinFlow;
            }
            ansFlow += MinFlow;
        }
    }
    printMinimumCut(1);

    return true;
}

int main() {

    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    read();

    bool repeat = true;
    while(repeat)
        repeat = generateFlow(1);
    printf("%d", ansFlow);

    return 0;
}

