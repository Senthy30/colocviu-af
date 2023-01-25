#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 36010;

FILE *IN;

struct edges{
    int x, cost;
}ans[NMAX];

vector <edges> edge[NMAX];
queue <int> Q;

int N, M, K;
bool add[NMAX], castle[NMAX];

int pos, sign;
char f[MAX];

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
    Read(N); Read(M); Read(K);
    for(int i = 1; i <= N; i++)
        ans[i].cost = 2e9;
    int a, b, c;
    for(int i = 1; i <= K; i++){
        Read(a);
        castle[a] = true;
        add[a] = true;
        ans[a].cost = 0;
        ans[a].x = a;
        Q.push(a);
    }
    for(int i = 1; i <= M; i++){
        Read(a); Read(b); Read(c);
        edge[a].push_back({b, c});
        edge[b].push_back({a, c});
    }
}

int main(){

    IN = fopen("catun.in", "r");
    freopen("catun.out", "w", stdout);

    read();

    while(!Q.empty()){
        int x = Q.front();
        Q.pop();
        add[x] = false;
        for(int i = 0; i < edge[x].size(); i++){
            int y = edge[x][i].x;
            int Cost = edge[x][i].cost;
            if(ans[y].cost > ans[x].cost + Cost){
                ans[y].cost = ans[x].cost + Cost;
                ans[y].x = ans[x].x;
                if(!add[y])
                    add[y] = true, Q.push(y);
            } else if(ans[y].cost == ans[x].cost + Cost){
                if(ans[y].x > ans[x].x){
                    ans[y].x = ans[x].x;
                    add[y] = true;
                    Q.push(y);
                }
            }
        }
    }

    for(int i = 1; i <= N; i++)
        if(!castle[i])
            printf("%d ", ans[i].x);
        else printf("0 ");

    return 0;
}
