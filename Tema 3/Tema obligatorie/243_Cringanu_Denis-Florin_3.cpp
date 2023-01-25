#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 155;

FILE *IN, *OUT;

int N, ans;
int father[2 * NMAX];
int capacity[2 * NMAX][2 * NMAX], flow[2 * NMAX][2 * NMAX];
bool seen[2 * NMAX];
vector <int> edges[2 * NMAX];
queue <int> Q;

int pos, sign;
char f[MAX];

// folosim algoritmul Edmonds-Karp
// dublam fiecare nod si le memoram de la 1 la n si de la n+1 la 2*n si adaugam un nod sursa numerotat cu 0 si un nod destinatie 2*n+1
// adaugam muchie intre sursa si toate nodurile (prima multime) cu capacitate gradul pentru iesire
// (la fel si pt a doua multime si destinatie pt gradul de intrare)
// adaug muchie de la orice nod din prima multime la orice alt nod din a doua multime cu capacitatea 1

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

bool bellman_ford(){
    Q.push(0);
    while(!Q.empty()){
        int node = Q.front();
        Q.pop();
        for(int i = 0; i < edges[node].size(); i++){
            int x = edges[node][i];
            if(!seen[x] && capacity[node][x] - flow[node][x] > 0){
                Q.push(x);
                father[x] = node;
                seen[x] = true;
            }
        }
    }
    if(!father[2 * N + 1])
        return false;
    int node = 2 * N + 1, Min;
    for(int i = N + 1; i <= 2 * N; i++)
        if(seen[i] && capacity[i][node] - flow[i][node] > 0){
            Min = capacity[i][node] - flow[i][node];
            for(int j = i; j != 0; j = father[j])
                if(Min > capacity[father[j]][j] - flow[father[j]][j])
                    Min = capacity[father[j]][j] - flow[father[j]][j];
            flow[i][node] += Min;
            flow[node][i] -= Min;
            for(int j = i; j != 0; j = father[j]){
                flow[father[j]][j] += Min;
                flow[j][father[j]] -= Min;
            }
            ans += Min;
        }
    return true;
}

int main(){

    IN = fopen("harta.in", "r");
    OUT = fopen("harta.out", "w");

    Read(N);
    int a, b;
    for(int i = 1; i <= N; i++){
        Read(a); Read(b);
        capacity[0][i] = a;
        edges[0].push_back(i);
        edges[i].push_back(0);
        capacity[N + i][2 * N + 1] = b;
        edges[N + i].push_back(2 * N + 1);
        edges[2 * N + 1].push_back(N + i);
        for(int j = N + 1; j <= 2 * N; j++){
            if(j == N + i) continue;
            capacity[i][j] = 1;
            edges[i].push_back(j);
            edges[j].push_back(i);
        }
    }

    bool retry = true;
    while(retry){
        retry = false;
        for(int i = 0; i <= 2 * N + 1; i++){
            seen[i] = 0;
            father[i] = 0;
        }
        retry = bellman_ford();
    }
    fprintf(OUT, "%d\n", ans);
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++){
            if(i == j) continue;
            if(flow[i][j + N] == 1)
                fprintf(OUT, "%d %d\n", i, j);
        }

    return 0;
}
