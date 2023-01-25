#include <bits/stdc++.h>

using namespace std;
const int NMAX = 100100;

bool ans;
int N;
bool wasSeen[NMAX];
int d[NMAX];
vector <int> edges[NMAX];
vector <vector <int> > partitionList;

// explicatie a
// facem un BFS din fiecare nod nevizitat si incercam sa aflam adancimea fiecarui nod
// daca exista o muchie de la un nod al carei paritate este aceeasi cu nodul catre care este muchia, atunci nu se poate efectua o bipartitie
// daca nu exista, atunci se poate

// explicatie b
// coloram nodurile dupa paritatea adancimii si le adaugam in 2 vectori, primul reprezinta cel cu un numar par la adancime, iar al doilea vector reprezinta cel cu un numar impar la adancime


void readNumber(int &val, int &currentIndex, string &s, char exceptionChar){
    for(; currentIndex < s.size(); currentIndex++){
        if(s[currentIndex] == exceptionChar)
            break;
        val = 10 * val + s[currentIndex] - '0';
    }
}

void read(){
    string s;
    getline(cin, s);

    int currentIndex = 0;
    for(; currentIndex < s.size(); currentIndex++)
        if(s[currentIndex] >= '0' && s[currentIndex] <= '9')
            break;
    // read N
    readNumber(N, currentIndex, s, ',');

    for(; currentIndex < s.size(); currentIndex++)
        if(s[currentIndex] == '['){
            currentIndex++;
            break;
        }
    // read edges
    for(; currentIndex < s.size(); currentIndex++){
        if(s[currentIndex] == ']')
            break;
        int x = 0, y = 0;
        currentIndex++;
        readNumber(x, currentIndex, s, ',');
        currentIndex++;
        readNumber(y, currentIndex, s, ']');
        currentIndex++;

        edges[x].push_back(y);
        edges[y].push_back(x);
    }
}

void transformInSth(int n, const vector<vector<int>>& dislikes){
    N = n;
    for(auto v : dislikes){
        int x = v[0];
        int y = v[1];
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
}

void BFS(int node){
    queue <int> Q;
    Q.push(node);
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(auto it : edges[node]){
            if(!wasSeen[it]){
                wasSeen[it] = true;
                Q.push(it);
                d[it] = d[node] + 1;
            }
        }
    }
}

void DFS(int node){
    wasSeen[node] = true;
    for(auto it : edges[node]){
        if(d[it] % 2 == d[node] % 2)
            ans = false;
        if(!wasSeen[it])
            DFS(it);
    }
}

void solvePartition(int node){
    partitionList[d[node] % 2].push_back(node);
    wasSeen[node] = true;
    for(auto it : edges[node])
        if(!wasSeen[node])
            solvePartition(it);
}

void resetWasSeen(){
    for(int i = 0; i <= N; i++)
        wasSeen[i] = false;
}

vector <vector <int> > possibleBipartition(int n, const vector<vector<int>> &dislikes){
    transformInSth(n, dislikes);
    for(int i = 1; i <= N; i++)
        if(!wasSeen[i])
            BFS(i);
    resetWasSeen();
    ans = true;
    for(int i = 1; i <= N; i++)
        if(!wasSeen[i])
            DFS(i);

    if(ans == false)
        return {};

    partitionList.push_back(vector <int> ());
    partitionList.push_back(vector <int> ());
    resetWasSeen();
    for(int i = 1; i <= N; i++)
        if(!wasSeen[i])
            solvePartition(i);

    return partitionList;
}

int main() {

    possibleBipartition(4, {{1,2},{1,3},{2,4}});

    return ans;
}
