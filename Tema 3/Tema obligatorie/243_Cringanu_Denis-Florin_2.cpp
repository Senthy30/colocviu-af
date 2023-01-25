#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const short NMAX = 20300;

struct obj {
    short first, second;
};

int N1, N2, M, S, D, ansFlow;

bool wasSeen[NMAX];
short dad[NMAX];

map <short, obj> flow[NMAX];
vector <short> edges[NMAX], directedEdges[NMAX];

// flow.first = capacity
// flow.second = flow
FILE *IN, *OUT;
int pos, sign, out;
char f[MAX], Out[MAX], str[10];

inline void Read(int &nr){
    sign = 0;
    nr = 0;
    while(f[pos] < '0' || f[pos] > '9'){
        if(f[pos] == '-') sign = 1;
        pos++;
        if(pos == MAX)
            fread(f, MAX, 1, IN), pos = 0;
    }
    while(f[pos] >= '0' && f[pos] <= '9'){
        nr = 10 * nr + f[pos++] - '0';
        if(pos == MAX)
            fread(f, MAX, 1, IN), pos = 0;
    }
    if(sign) nr =- nr;
}

inline void Write_Ch(char ch){
    Out[out++] = ch;
    if(out == MAX)
        fwrite(Out, MAX, 1, OUT), out = 0;
}

inline void Write_Int(int nr){
    int x = 0;
    if(nr < 0) Write_Ch('-'), nr = -nr;
    do{
        str[x++] = nr % 10 + '0';
        nr /= 10;
    } while(nr);
    while(x > 0)
        Write_Ch(str[--x]);
}

void read(){
    Read(N1); Read(N2); Read(M);
    int x, y;
    S = 0;
    D = N1 + N2 + 1;
    vector <pair <short, short> > tempEdges;
    for(int i = 1; i <= M; i++){
        Read(x); Read(y);
        tempEdges.push_back(make_pair(x, y));
    }
    sort(tempEdges.begin(), tempEdges.end());

    for(int i = 0; i < M; i++){
        x = tempEdges[i].first;
        y = tempEdges[i].second;
        directedEdges[x].push_back(N1 + y);
        edges[x].push_back(N1 + y);
        edges[N1 + y].push_back(x);
        flow[x][N1 + y] = {1, 0};
    }

    tempEdges.clear();

    for(short node = 1; node <= N1; node++){
        directedEdges[S].push_back(node);
        edges[S].push_back(node);
        edges[node].push_back(S);
        flow[S][node] = {1, 0};
    }
    for(short node = N1 + 1; node <= N1 + N2; node++){
        directedEdges[node].push_back(D);
        edges[D].push_back(node);
        edges[node].push_back(D);
        flow[node][D] = {1, 0};
    }
}

// aplic algoritmul de flux, pornesc un BFS din nodul 0 si incerc sa ajung in nodul D pe muchiile care inca nu
// si-au atins capacitatea maxima, iar pentru fiecare nod retin nodul de unde am venit
// pentru toti vecinii lui N, calculez fluxul cu care pot sa ajung intr-un vecin de a lui, uitandu-ma la tatii acestuia
// insumez toate fluxurile gasite si obtin rezultatul
// aplic un BFS pe garful citit (orientat) si verific daca mai pot trimite flux pe o muchie intre 2 noduri
// pornesc din nodul 1 si aplic BFS, daca pe o muchie capacitate de flux este maxim, atunci adaug muchia intr-un vector,
// la final verific daca am putut ajunge in nodul N, iar daca nu, afisez muchia care reprezinta un cuplaj

void printMinimumCut(short node){
    for(short i = 0; i <= D; i++)
        wasSeen[i] = false;
    vector <pair <short, short> > cutEdges;
    queue <short> Q;
    Q.push(node);
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(short i = 0; i < directedEdges[node].size(); ++i){
            short it = directedEdges[node][i];
            if(node != S && it != D && flow[node][it].first - flow[node][it].second == 0){
                cutEdges.push_back(make_pair(node, it - N1));
                continue;
            }
            if(!wasSeen[it]) {
                wasSeen[it] = true;
                Q.push(it);
            }
        }
    }
    for(short i = 0; i < cutEdges.size(); ++i){
        Write_Int(cutEdges[i].first); Write_Ch(' ');
        Write_Int(cutEdges[i].second); Write_Ch('\n');
    }
}

bool generateFlow(short node){
    for(short i = 0; i <= D; ++i){
        wasSeen[i] = false;
        dad[i] = 0;
    }
    queue <short> Q;
    Q.push(node);
    wasSeen[node] = true;
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(short i = 0; i < edges[node].size(); ++i){
            short it = edges[node][i];
            if(!wasSeen[it] && flow[node][it].first - flow[node][it].second > 0){
                wasSeen[it] = true;
                dad[it] = node;
                Q.push(it);
            }
        }
    }

    if(!dad[D])
        return false;

    node = D;
    for(short i = 0; i < edges[node].size(); ++i){
        short it = edges[node][i];
        short MinFlow = flow[it][node].first - flow[it][node].second;
        short PosFlow = 0;
        if(MinFlow > 0){
            for(short j = it; j != 0; j = dad[j]){
                PosFlow = flow[dad[j]][j].first - flow[dad[j]][j].second;
                if(PosFlow < MinFlow)
                    MinFlow = PosFlow;
            }
            if(!MinFlow)
                continue;
            flow[it][node].second += MinFlow;
            flow[node][it].second -= MinFlow;
            for(short j = it; j != 0; j = dad[j]){
                flow[dad[j]][j].second += MinFlow;
                flow[j][dad[j]].second -= MinFlow;
            }
            ansFlow += MinFlow;
        }
    }

    return true;
}

int main() {

    IN = fopen("cuplaj.in", "r");
    OUT = fopen("cuplaj.out", "w");

    read();

    bool repeat = true;
    while(repeat)
        repeat = generateFlow(0);
    Write_Int(ansFlow); Write_Ch('\n');
    printMinimumCut(0);

    if(out > 0) fwrite(Out, 1, out, OUT);

    return 0;
}
