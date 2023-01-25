#include <bits/stdc++.h>
#define INF 1e18

using namespace std;
const int NMAX = 2010;

ifstream fin("retea2.in");
ofstream fout("retea2.out");

struct coord{
    int x, y;
}cent[NMAX], bloc[NMAX];

int N, M;
long long cost[NMAX];
long double ans;
bool add[NMAX];

long long dist(coord a, coord b){
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

int main(){

    fin >> N >> M;
    for(int i = 1; i <= N; i++)
        fin >> cent[i].x >> cent[i].y;
    for(int i = 1; i <= M; i++){
        fin >> bloc[i].x >> bloc[i].y;
        cost[i] = INF;
        for(int j = 1; j <= N; j++)
            cost[i] = min(cost[i], dist(cent[j], bloc[i]));
    }

    for(int i = 1; i <= M; i++){
        int node = 0;
        long long Min = INF;
        for(int j = 1; j <= M; j++){
            if(!add[j] && Min > cost[j])
                Min = cost[j], node = j;
        }
        add[node] = true;
        ans += sqrt((long double)Min);
        for(int j = 1; j <= M; j++)
            if(!add[j])
                cost[j] = min(cost[j], dist(bloc[node], bloc[j]));
    }
    fout << setprecision(10) << fixed << ans << '\n';

    return 0;
}
