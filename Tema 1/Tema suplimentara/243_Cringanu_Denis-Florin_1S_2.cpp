#include <bits/stdc++.h>

using namespace std;
const int NMAX = 1015;

int di[4] = {0, 0, -1, 1};
int dj[4] = {-1, 1, 0 ,0};

ifstream fin("padure.in");
ofstream fout("padure.out");

int pl, pc, cl, cc, N, M;
int H[NMAX][NMAX], Lee[NMAX][NMAX];

deque <pair <int, int> > Q;

// aplicam algoritmul lui Lee pentru rezolvare problemei, doar ca in loc de queue, vom folosi un deque (o coada cu doua capete)
// vom incerca sa prioritizam casutele cu aceeasi valoare
// in fruntea cozii vom adauga casutele vecine cu o casuta vizitata si care are aceeasi valoare cu aceasta
// in spatele cozii vom adauga casutele vecine cu o casuta vizitata si care are valoarea diferita cu aceasta
// astfel vom calcula costul minim de a ajunge intr-o casuta [i, j] care va fi retinut in matricea Lee

bool OK(int i, int j){
    if(i < 1 || j < 1 || i > N || j > M)
        return false;
    return true;
}

void lee(){
    Q.push_back(make_pair(pl, pc));
    Lee[pl][pc] = 0;
    while(!Q.empty()){
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop_front();
        for(int d = 0; d < 4; d++){
            int i_1 = i + di[d];
            int j_1 = j + dj[d];
            if(H[i_1][j_1] != H[i][j]){
                if(OK(i_1, j_1) && Lee[i_1][j_1] > Lee[i][j] + 1){
                    Lee[i_1][j_1] = Lee[i][j] + 1;
                    if(i_1 != cl || j_1 != cc)
                        Q.push_back(make_pair(i_1, j_1));
                }
            } else {
                if(OK(i_1, j_1) && Lee[i_1][j_1] > Lee[i][j]){
                    Lee[i_1][j_1] = Lee[i][j];
                    if(i_1 != cl || j_1 != cc)
                        Q.push_front(make_pair(i_1, j_1));
                }
            }
        }
    }
}

int main(){
    fin >> N >> M >> pl >> pc >> cl >> cc;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            fin >> H[i][j];
            Lee[i][j] = 100000000;
        }
    }

    lee();
    fout << Lee[cl][cc];

    return 0;
}
