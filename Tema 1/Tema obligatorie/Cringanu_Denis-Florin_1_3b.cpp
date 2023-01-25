#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100100;

int N, M, nodeForCicle = -1;
bool wasSeen[NMAX];
int st[NMAX], SoS;
int v[NMAX], dp[NMAX];
vector <int> ans;
vector <int> edges[NMAX];

// explicatie a
// ne folosim de algoritmul de sortare topologica
// vectorul dp ne arata daca nodul i mai are ramasa vreo muchie care n-a fost parcursa si intra in el
// daca vectorul dp este tot plin de zero,  atunci se pot parcurge toate cursurile, altfel nu

// explicatie b
// daca nu se pot parcurge toate cursurile, atunci inseamna ca exista un ciclu
// poate a gasi ciclul ne folosim de un DFS si daca un nod se repeta de 2 ori, atunci el inchide un ciclu
// folosindu-ne de o stiva cu istoricul de noduri, putem afla prin ce noduri am trecut si putem returna lista cu nodurile ciclului

void read(int numCourses, const vector< vector <int> > &prerequisites){
    N = numCourses;
    for(auto v : prerequisites){
        int x = v[0];
        int y = v[1];
        edges[y].push_back(x);
        dp[x]++;
    }
}

void dfs(int node){
    wasSeen[node] = true;
    ans.push_back(node);
    for(auto it : edges[node])
        if(!wasSeen[it]){
            --dp[it];
            if(!dp[it]) dfs(it);
        }
}

void resetWasSeen(){
    for(int i = 0; i < N; i++)
        wasSeen[i] = false;

}

void dfsToFindCicle(int node){
    st[SoS++] = node;
    wasSeen[node] = true;
    for(auto it : edges[node]){
        if(wasSeen[it]) {
            nodeForCicle = it;
            int i = 0;
            for(; i < SoS; i++)
                if(st[i] == nodeForCicle)
                    break;
            for(; i < SoS; i++)
                ans.push_back(st[i]);
        }
        if(nodeForCicle != -1)
            return;
        dfsToFindCicle(it);
    }
    st[--SoS] = 0;
}

vector<int> findOrder(int numCourses, const vector< vector <int> > &prerequisites) {
    read(numCourses, prerequisites);
    for(int i = 0; i < N; i++)
        if(!wasSeen[i] && !dp[i])
            dfs(i);
    bool isOk = true;
    for(int i = 0; i < N; i++)
        if(dp[i] > 0)
            isOk = false;

    if(!isOk){
        cout << "Cicle!\n";
        ans = {};
        resetWasSeen();
        for(int i = 0; i < N && nodeForCicle == -1; i++)
            if(!wasSeen[i])
                dfsToFindCicle(i);
    }

    return ans;
}



int main() {

    vector <int> v = findOrder(2, {{1,0}, {2,1}, {3,2}, {0,3}});
    for(auto element : v)
        cout << element << ' ';

    return 0;
}
