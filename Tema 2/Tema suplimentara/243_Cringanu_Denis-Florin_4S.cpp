#include <bits/stdc++.h>

using namespace std;
const int NMAX = 10010;

struct obj{
    int x, cost;
};

struct objV {
    int x, y, cost;
}temp;

bool wasFound;
int N, M, Q, currentCost;
bool wasSeen[NMAX];
int comp[NMAX];
vector <objV> v, st;
vector <obj> edges[NMAX];

bool cmp(objV a, objV b){
    return a.cost < b.cost;
}

void read(){
    scanf("%d%d%d", &N, &M, &Q);
    int x, y, z;
    for(int i = 1; i <= M; i++){
        scanf("%d%d%d", &x, &y, &z);
        v.push_back({x, y, z});
    }
    for(int i = 1; i <= N; i++)
        comp[i] = i;
    sort(v.begin(), v.end(), cmp);
}

inline int Find(int x){
    int root = x, aux;
    while(root != comp[root])
        root = comp[root];
    while(x != root){
        aux = comp[x];
        comp[x] = root;
        x = aux;
    }
    return x;
}

inline void Union(int x, int y){
    comp[x] = y;
}

void extractMaxValue(int nodeRepeat){
    int i = 0;
    for(; i < st.size(); i++)
        if(st[i].x == nodeRepeat)
            break;
    temp = {0, 0, -1};
    for(; i < st.size(); i++)
        if(st[i].cost > temp.cost)
            temp = st[i];
    wasFound = true;
}

void getMaxValueFromCicle(int dad, int node, int cost){
    if(wasFound)
        return;

    wasSeen[node] = true;
    for(auto it : edges[node]){
        if(wasFound)
            break;
        if(it.x == dad)
            continue;

        st.push_back({node, it.x, it.cost});
        if(!wasSeen[it.x])
            getMaxValueFromCicle(node, it.x, it.cost + cost);
        else
            extractMaxValue(it.x);
        st.pop_back();
    }
}

vector<obj>::iterator searchElement(objV a){
    vector<obj>::iterator it = edges[a.x].begin();
    for(; it != edges[a.x].end(); it++)
        if(it->x == a.y && it->cost == a.cost)
            return it;
    return edges[a.x].end();
}

void deleteEdge(objV a){
    vector<obj>::iterator it = searchElement(a);
    //printf("(%d %d %d)\n", a.x, it->x, it->cost);
    if(it != edges[a.x].end())
        edges[a.x].erase(it, it + 1);
}

void solve(){
    objV tempR;

    scanf("%d%d", &tempR.x, &tempR.y);
    edges[tempR.x].push_back({tempR.y, -1});
    edges[tempR.y].push_back({tempR.x, -1});

    for(int i = 1; i <= N; i++)
        wasSeen[i] = false;
    wasFound = false;
    getMaxValueFromCicle(0, 1, 0);
    printf("%d\n", temp.cost - 1);

    deleteEdge({tempR.x, tempR.y, -1});
    deleteEdge({tempR.y, tempR.x, -1});
}

int main() {

    freopen("apm2.in", "r", stdin);
    freopen("apm2.out", "w", stdout);

    read();

    int x, y;
    for(int i = 0; i < M; i++){
        x = Find(v[i].x);
        y = Find(v[i].y);
        if(x != y){
            Union(x, y);
            currentCost += v[i].cost;
            edges[v[i].x].push_back({v[i].y, v[i].cost});
            edges[v[i].y].push_back({v[i].x, v[i].cost});
        }
    }

    for(int i = 1; i <= Q; i++)
        solve();
}
