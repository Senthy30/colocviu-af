#include <bits/stdc++.h>

using namespace std;

ifstream fin("adn.in");
ofstream fout("adn.out");

const int inf = 1e9;
int n, val[20][20], cat[20];
string lant[20], answer;
bool ok[20];
int dp[20][(1 << 19)];
vector <int> v;

// aplic KMP pentru fiecare pereche de cuvinte din input, pentru o pereche de cuvinet (i, j) verific daca cuvantul j este inclus in cuvantul i
// val[i][j] = lungimea maxima a unui sufix a lui i care este prefix pentru j
// calculez suma lungimile cuvintelor care nu sunt incluse in alte cuvinte si adauga indexul cuvintelor intr-un vector
// aplic o dinamica pe stari exponentiale dp[i][mask] = lungimea comuna a cuvintelor daca la cuvintele din mask (care au bitul 1) adaug cuvantul i
// calculez apoi pentru fiecare cuvant cat caractere voi lua din el

int kmp(string s) {
    int nn = (int) s.length(), l = 0;
    vector<int> pi(nn);
    for (int i = 1; i < nn; ++i){
        while (l > 0 && s[l] != s[i]){
            l = pi[l - 1];
        }
        if (s[l] == s[i]){
            ++l;
        }
        pi[i] = l;
    }
    int i = 0, contor = 0;
    while (s[i] != '#'){
        ++i;
        ++contor;
    }
    ++i;
    while (i < nn){
        if (pi[i] == contor) return contor;
        ++i;
    }
    return pi[nn - 1];
}

int main(){
    fin >> n;
    for (int i = 1; i <= n; ++i){
        fin >> lant[i];
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            if (i == j){
                continue;
            }
            string a = lant[i], b = lant[j];
            int ans = kmp(b + "#" + a);
            val[i][j] = ans;
            if (ans == b.size()){
                ok[j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i){
        if (!ok[i]){
            v.push_back(i);
            sum += lant[i].size();
        }
    }
    n = v.size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < (1 << n); ++j){
            dp[i][j] = -inf;
        }
    }
    for (int i = 0; i < n; ++i){
        dp[i][(1 << i)] = 0;
    }
    for (int mask = 1; mask < (1 << n); ++mask){
        for (int j = 0; j < n; ++j){
            if (dp[j][mask] != -inf){
                for (int k = 0; k < n; ++k){
                    if (j == k){
                        continue;
                    }
                    if (((mask >> k) & 1) == 0){
                        dp[k][(mask | (1 << k))] = max(dp[k][(mask | (1 << k))], dp[j][mask] + val[v[j]][v[k]]);
                    }
                }
            }
        }
    }
    int minim = 1e9, nod = 0;
    for (int i = 0; i < n; ++i){
        if (sum - dp[i][(1 << n) - 1] < minim){
            minim = sum - dp[i][(1 << n) - 1];
            nod = i;
        }
    }
    int mask = ((1 << n) - 1);
    mask -= (1 << nod);
    vector <int> aux;
    aux.push_back(nod);
    cat[nod] = lant[v[nod]].size();
    while (mask){
        int nod2 = 0;
        for (int i = 0; i < n; ++i){
            if ((mask >> i) & 1){
                if (dp[i][mask] + val[v[i]][v[nod]] == dp[nod][mask + (1 << nod)]){
                    nod2 = i;
                    break;
                }
            }
        }
        int contor = val[v[nod2]][v[nod]];
        cat[nod2] = lant[v[nod2]].size() - contor;
        aux.push_back(nod2);

        nod = nod2;
        mask -= (1 << nod);
    }
    for (int i = aux.size() - 1; i >= 0; --i){
        int nod = aux[i];
        for (int j = 0; j < cat[nod]; ++j){
            fout << lant[v[nod]][j];
        }
    }
    fin.close();
    fout.close();
    return 0;
}
