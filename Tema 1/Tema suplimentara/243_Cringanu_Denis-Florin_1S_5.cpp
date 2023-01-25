#include <bits/stdc++.h>

using namespace std;

int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, -1, 0, 1};

int N, M, area, maxArea;
bool wasSeen[55][55];
bool matrix[55][55];

// aplicam algoritmul de Fill pentru fiecare casuta din matricea data care nu a fost vizitata si casuta este o insula
// cand efectuam algoritmul lui Fill calculam si aria pe care o are intreaga insula
// la final vom retine doar maximul dintre fiecare insula calculata

void read(vector<vector<int> >& grid){
    N = grid.size();
    M = grid[0].size();
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            matrix[i][j] = grid[i][j];
}

bool checkOk(int nexti, int nextj){
    if(nexti >= 0 && nextj >= 0 && nexti < N && nextj < M && matrix[nexti][nextj] && !wasSeen[nexti][nextj])
        return true;
    return false;
}

void fillMatrix(int i, int j){
    queue <pair <int, int> > Q;
    Q.push(make_pair(i, j));
    area = 1;
    wasSeen[i][j] = true;
    while(!Q.empty()){
        i = Q.front().first;
        j = Q.front().second;
        Q.pop();
        for(int d = 0; d < 4; d++){
            int nexti = i + di[d];
            int nextj = j + dj[d];
            if(checkOk(nexti, nextj)){
                wasSeen[nexti][nextj] = true;
                area++;
                Q.push(make_pair(nexti, nextj));
            }
        }
    }
}

int maxAreaOfIsland(vector<vector<int> >& grid) {
    read(grid);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(!wasSeen[i][j] && matrix[i][j]){
                fillMatrix(i, j);
                if(area > maxArea)
                    maxArea = area;
            }
        }
    }

    return maxArea;
}

int main(){

    vector <vector <int> > grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};
    cout << maxAreaOfIsland(grid);

    return 0;
}
