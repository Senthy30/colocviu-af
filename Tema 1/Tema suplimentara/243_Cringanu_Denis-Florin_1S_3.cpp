#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100100;

int N, M, X, Y;
int depthX[NMAX], depthY[NMAX], frecv[NMAX];
bool wasSeen[NMAX];
vector <int> ans;
vector <int> graph[NMAX];

// facem un BFS atat din nodul X cat si din nodul Y
// pentru un nod, daca distanta dintre el si X + distanta dintre el si Y este egala cu distanta din X si Y, atunci inseamna ca nodul curent face parte dintr-un lant de lungime minima dintre X si Y
// vom face frecventa pe adancime din X catre Y (cate noduri exista pe un anumit nivel)
// daca pe un anumit nivel exista un sigur nod, atunci acel nod face parte din toate lanturile de lungime minima dintre X si Y

void read(){
    scanf("%d%d%d%d", &N, &M, &X, &Y);
    for(int i = 0; i < M; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
}

void BFS(int node, int type){
    queue <int> Q;
    Q.push(node);
    for(int i = 1; i <= N; i++)
        wasSeen[i] = false;
    wasSeen[node] = true;

    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(auto it : graph[node]){
            if(!wasSeen[it]){
                if(!type)
                    depthX[it] = depthX[node] + 1;
                else depthY[it] = depthY[node] + 1;
                Q.push(it);
                wasSeen[it] = true;
            }
        }
    }
}

int main(){

    freopen("graf.in", "r", stdin);
    freopen("graf.out", "w", stdout);

    read();
    BFS(X, 0);
    BFS(Y, 1);

    int dmin = depthX[Y];
    for(int i = 1; i <= N; i++){
        if(depthX[i] + depthY[i] <= dmin)
            frecv[depthX[i]]++;
    }

    for(int i = 1; i <= N; i++)
        if(depthX[i] + depthY[i] <= dmin && frecv[depthX[i]] == 1)
            ans.push_back(i);

    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);

    return 0;
}
