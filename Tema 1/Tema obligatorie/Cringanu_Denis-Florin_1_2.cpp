#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100100;

bool ans = true;
int N, M, currentIndex;
bool wasSeen[NMAX];
int v[NMAX];
map <int, bool> isNeigh[NMAX];
vector <int> edges[NMAX];

// explicatie
// parcurgem vectorul dat si incercam sa vedem daca urmatorul element din vector este fiu al elementului curent
// daca i-am vizitat tot fii unui nod, atunci ne intoarcem la nodul tata

void read(){
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++)
        scanf("%d", &v[i]);
    for(int i = 1; i <= M; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
        isNeigh[x][y] = true;
        isNeigh[y][x] = true;
    }
}

bool dfs(int node){
    wasSeen[node] = true;
    for(auto it : edges[node]){
        if(!ans)
            break;
        if(!wasSeen[it]){
            currentIndex++;

            if(isNeigh[node][v[currentIndex]] == true) {
                dfs(v[currentIndex]);
            } else ans = false;
        }
    }
}

int main() {

    read();
    currentIndex = 1;
    dfs(1);
    cout << ans;

    return ans;
}
