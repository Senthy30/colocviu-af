#include <bits/stdc++.h>

using namespace std;

struct obj3 {
    int x, y, z;
};

struct obj4 {
    int x, y, z, w;
};

int N, M;
int comp[100100];
vector <obj3> edges;
vector <obj4> Q;
vector <bool> ans;

int Find(int i){
    if(comp[i] < 0)
        return i;
    else return comp[i] = Find(comp[i]);
}
inline void Union(int i, int j){
    i = Find(i), j = Find(j);
    if (i != j)
        comp[i] = j;
}

inline bool cmp3(obj3 a, obj3 b){
    return a.z < b.z;
}

inline bool cmp4(obj4 a, obj4 b){
    return a.z < b.z;
}

vector<bool> distanceLimitedPathsExist(int n, vector< vector<int> > &edgeList, vector< vector<int> > &queries) {
    int i = 0, j = 0;
    for(int k = 0; k < n; k++)
        comp[k] = k;
    for(auto it : edgeList)
        edges.push_back({it[0], it[1], it[2]});
    for(auto it : queries){
        Q.push_back({it[0], it[1], it[2], i++});
        ans.push_back(false);
    }
    sort(edges.begin(), edges.end(), cmp3);
    sort(Q.begin(), Q.end(), cmp4);

    i = 0;
    while(j < Q.size()){
        while(i < edges.size() && edges[i].z < Q[j].z){
            Union(edges[i].x, edges[i].y);
            ++i;
        }
        if(Find(Q[j].x) == Find(Q[j].y))
            ans[Q[j].w] = true;
        ++j;
    }

    return ans;
}

int main() {

    vector< vector<int> > edgeList = {{0,1,10},{1,2,5},{2,3,9},{3,4,13}};
    vector< vector<int> > queries = {{0,4,14},{1,4,13}};

    vector <bool> ans = distanceLimitedPathsExist(5, edgeList, queries);

    for(auto it : ans)
        cout << it << ' ';

}
