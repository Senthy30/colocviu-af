#include <bits/stdc++.h>

using namespace std;

int N, M;
vector < pair<int, double> > edges[10010];
vector <double> v;

void read(int n, const vector<vector<int>>& ed, const vector<double>& succProb){
    N = n;
    int currentIndex = 0;
    for(auto it : ed){
        edges[it[0]].push_back(make_pair(it[1], succProb[currentIndex]));
        edges[it[1]].push_back(make_pair(it[0], succProb[currentIndex]));
        currentIndex++;
    }
    for(int i = 0; i < N; i++)
        v.push_back(0);
}

void BellmanFord(int node, double prob){
    queue < pair <int, double> > Q;
    Q.push(make_pair(node, prob));
    v[node] = prob;
    while(!Q.empty()){
        node = Q.front().first;
        prob = Q.front().second;
        Q.pop();
        for(auto it : edges[node]){
            if(prob * it.second > v[it.first]){
                v[it.first] = prob * it.second;
                Q.push(make_pair(it.first, v[it.first]));
            }
        }
    }
}

double maxProbability(int n, const vector<vector<int>>& edges, const vector<double>& succProb, int start, int end) {
    read(n, edges, succProb);
    BellmanFord(start, 1);

    return v[end];
}

int main() {

    maxProbability(3, {{0,1},{1,2},{0,2}}, {0.5,0.5,0.2}, 0, 2);

    return 0;
}
