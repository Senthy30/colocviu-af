#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
unordered_map <int, vector<int> > edges;
unordered_map <int, int> degree;

// calculam gradul pentru fiecare nod dupa care vom parcurge graful plecand din nodul care are gradul 1, sau din oricare nod daca tot graful este un ciclu
// ne folosim de o stiva pe care adaugam nodul de plecare dupa care pentru toti vecinii nodului din varful stivei adaugam vecinii pe stiva
// repetam procesul pana cand stiva devine goala

vector< vector<int> > validArrangement(const vector<vector<int>>& pairs) {
    for(auto it : pairs){
        edges[it[0]].push_back(it[1]);
        degree[it[0]]++;
        degree[it[1]]--;
    }
    int startNode = -1;
    for(auto it : degree){
        if(it.second == 1){
            startNode = it.first;
            break;
        }
        if(startNode == -1)
            startNode = it.first;
    }

    vector <int> v;
    vector <int> stk = {startNode};
    while(stk.size()){
        while(edges[stk.back()].size()){
            int x = edges[stk.back()].back();
            edges[stk.back()].pop_back();
            stk.push_back(x);
        }
        v.push_back(stk.back());
        stk.pop_back();
    }

    reverse(v.begin(), v.end());
    vector< vector <int> > ans;
    for(int i = 0; i < v.size() - 1; i++)
        ans.push_back({v[i], v[i + 1]});

    return ans;
}
};
