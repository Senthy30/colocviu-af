#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 100010;

FILE *IN;

int N, M;
int comp[NMAX];

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

int Find(int x){
    int root = x, aux;

    while(comp[root] != root)
        root = comp[root];

    while(x != root){
        aux = comp[x];
        comp[x] = root;
        x = aux;
    }

    return x;
}

void Union(int x, int y){
    comp[Find(x)] = Find(y);
}

int main(){

    IN = fopen("disjoint.in", "r");
    freopen("disjoint.out", "w", stdout);

    Read(N); Read(M);
    for(int i = 1; i <= N; i++)
        comp[i] = i;

    int tip, x, y;
    for(int i = 1; i <= M; i++){
        Read(tip); Read(x); Read(y);
        if(tip == 1)
            Union(x, y);
        else{
            if(Find(x) == Find(y))
                printf("DA\n");
            else printf("NU\n");
        }
    }

    return 0;
}
