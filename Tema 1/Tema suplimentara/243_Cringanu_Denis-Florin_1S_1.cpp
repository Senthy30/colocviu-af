#include <bits/stdc++.h>

using namespace std;

int N, cnt = 1;
int upper[100100], wasSeen[100100];
vector <int> edges[100100];
vector <vector <int> > ans;

// pentru fiecare nod vom tine un vector upper in care va fi retinut adancimea minima a unui nod stramos care are muchie la nodul curent sau la unul dintre mostenitorii lui
// pentru un nod, fie un fiul al acestuia, daca upper[fiu] > adancimea nodului curent, atunci inseamna ca intre nod si fiu exista o muchie critica

void read(int n, vector<vector<int>>& connections){
    N = n;
    for(auto it : connections){
        edges[it[0]].push_back(it[1]);
        edges[it[1]].push_back(it[0]);
    }
}

void dfs(int node, int dad){
    upper[node] = wasSeen[node] = cnt++;
    for(auto it : edges[node]){
        if(!wasSeen[it])
            dfs(it, node), upper[node] = min(upper[node], upper[it]);
        else if(it != dad)
            upper[node] = min(upper[node], upper[it]);
        if(upper[it] > wasSeen[node])
            ans.push_back({node, it});
    }
}

vector <vector <int> > criticalConnections(int n, vector<vector<int>>& connections) {
    read(n, connections);
    dfs(0, -1);

    return ans;
}

int main(){

    vector <vector <int> > inputEdges = {{1,0},{2,0},{3,0},{4,1},{4,2},{4,0}};
    vector <vector <int> > rez = criticalConnections(5, inputEdges);
    for(auto it : rez)
        cout << it[0] << ' ' << it[1] << '\n';

    return 0;
}
