#include <bits/stdc++.h>

using namespace std;

const int NMAX = 350;
const int INF = 2e9;

vector <int> edges[NMAX + 1];
int cost[NMAX + 1][NMAX + 1];
int flux[NMAX + 1][NMAX + 1];
int p[NMAX + 1];

int dist[NMAX + 1];
bool viz[NMAX + 1];
int fakedist[NMAX + 1];
int realdist[NMAX + 1];

bool inQueue[NMAX + 1];

int n, s, d;

bool bellman( int node ) {
    for ( int i = 0; i <= n; i ++ ) dist[i] = INF;
    queue <int> q;
    q.push( node );
    dist[node] = 0;
    while ( !q.empty() ) {
        int node = q.front();
        q.pop();
        inQueue[node] = false;
        for ( auto i : edges[node] ) {
            if ( flux[node][i] > 0 && dist[i] > dist[node] + cost[node][i] ) {
                dist[i] = dist[node] + cost[node][i];
                if ( !inQueue[i] ) {
                    q.push( i );
                    inQueue[i] = 1;
                }
            }
        }
    }
    return ( dist[d] != INF );
}
bool flow() {
    priority_queue <pair<int, int>> pq;
    for ( int i = 0; i <= n; i ++ ) {
        p[i] = 0;
        viz[i] = 0;
        realdist[i] = dist[i];
        fakedist[i] = INF;
    }
    p[s] = -1;
    dist[s] = fakedist[s] = 0;
    pq.push( { 0, s } );
    while ( !pq.empty() ) {
        int node = pq.top().second;
        pq.pop();
        if ( !viz[node] ) {
            viz[node] = 1;
            for ( auto it : edges[node] ) {
                if ( flux[node][it] > 0 && ( !p[it] || fakedist[node] + realdist[node] + cost[node][it] - realdist[it] < fakedist[it] ) ) {
                    p[it] = node;
                    fakedist[it] = fakedist[node] + realdist[node] + cost[node][it] - realdist[it];
                    dist[it] = dist[node] + cost[node][it];
                    pq.push( { -fakedist[it], it } );
                }
            }
        }
    }
    return fakedist[d] != INF;
}
int main() {
    ifstream fin( "fmcm.in" );
    ofstream fout( "fmcm.out" );

    int m, i, a, b, min_cost;
    fin >> n >> m >> s >> d;
    for ( i = 0; i < m; i ++ ) {
        fin >> a >> b;
        fin >> flux[a][b] >> cost[a][b];
        edges[a].push_back( b );
        edges[b].push_back( a );
        cost[b][a] = -cost[a][b];
    }

    bellman( s );
    min_cost = 0;

    while ( flow() ) {
        int f = INF, c = 0;
        for ( int i = d; i != s; i = p[i] ) {
            f = min( f, flux[p[i]][i] );
            c += cost[p[i]][i];
        }
        for ( int i = d; i != s; i = p[i] ) {
            flux[p[i]][i] -= f;
            flux[i][p[i]] += f;
        }
        min_cost += c * f;
    };
    fout << min_cost;
    return 0;
}
