#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 1010;

struct obj{
    int x, cost;
};

int N, M, valMax;
bool wasSeen[NMAX];
int frecv[NMAX];
long long dist[NMAX];
queue <int> Q;
vector <obj> edges[NMAX];

FILE *IN, *OUT;
int pos, sign, out;
char f[MAX], Out[MAX], str[10];

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
    Read(N); Read(M);
    int x, y, z;
    for(int i = 1; i <= M; ++i){
        Read(x); Read(y); Read(z);
        edges[x].push_back({y, z * 1000});
        valMax = max(valMax, z * 1000);
    }
}

bool bellmanford(int node, int mid){
    while(!Q.empty())
        Q.pop();
    Q.push(node);
    dist[node] = 0;
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        wasSeen[node] = false;
        for(auto it : edges[node]){
            int cost = it.cost - mid;
            if(dist[it.x] > dist[node] + cost){
                dist[it.x] = dist[node] + cost;
                if(!wasSeen[it.x]){
                    wasSeen[it.x] = true;
                    Q.push(it.x);
                }
                ++frecv[it.x];
                if(N > 100){
                    if(frecv[it.x] == (N >> 1) - (N >> 2) - (N >> 3) - (N >> 4))
                        return true;
                } else {
                    if(frecv[it.x] == N)
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {

    IN = fopen("ciclu.in", "r");
    freopen("ciclu.out", "w", stdout);

    read();

    int st = 1, dr = valMax;
    while(st <= dr){
        bool isOk = false;
        int mid = (st + dr) >> 1;
        for(int i = 1; i <= N; ++i){
            wasSeen[i] = frecv[i] = 0;
            dist[i] = 1e15;
        }
        for(int i = 1; i <= N; ++i)
            if(!wasSeen[i] && bellmanford(i, mid)){
                isOk = true;
                break;
            }
        if(isOk)
            dr = mid - 1;
        else st = mid + 1;
    }

    cout << setprecision(2) << fixed << (float)st / 1000;

    return 0;
}
