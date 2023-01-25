#include <bits/stdc++.h>

using namespace std;

struct obj{
    string s1, s2;
    int val;
};

int k, N;
vector <string> str;
vector <obj> strPair;
unordered_map <string, int> clusterWord;

ifstream fin("cuvinte.in");

int distLev(string s1, string s2) {
    int l1 = s1.length();
    int l2 = s2.length();

    int dp[2][l1 + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i <= l1; i++)
        dp[0][i] = i;

    for (int i = 1; i <= l2; i++) {
        for (int j = 0; j <= l1; j++) {
            if (j == 0)
                dp[i % 2][j] = i;
            else if (s1[j - 1] == s2[i - 1])
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
            else
                dp[i % 2][j] = 1 + min(dp[(i - 1) % 2][j], min(dp[i % 2][j - 1], dp[(i - 1) % 2][j - 1]));
        }
    }

    return dp[l2 % 2][l1];
}

void read(){
    string temp;
    while(fin >> temp){
        str.push_back(temp);
        ++N;
        //cout << temp << ' ';
    }
    cout << "k = "; cin >> k;
}

bool cmp(obj a, obj b) {
    return a.val < b.val;
}

int main() {

    read();

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int levDist = distLev(str[i], str[j]);
            strPair.push_back({str[i], str[j], levDist});
        }
    }

    sort(strPair.begin(), strPair.end(), cmp);

    for (int i = 1; i <= str.size(); ++i)
        clusterWord[str[i - 1]] = i;

    for (int i = 1; i <= N - k; ++i) {
        int j = 0;
        while (clusterWord[strPair[j].s1] == clusterWord[strPair[j].s2])
            ++j;

        int cluster1 = clusterWord[strPair[j].s1];
        int cluster2 = clusterWord[strPair[j].s2];
        int minCluster = min(cluster1, cluster2);
        for (auto& cuv: clusterWord)
            if (cuv.second == cluster1 || cuv.second == cluster2)
                cuv.second = minCluster;
    }

    int minDif = 2e9;
    for (auto cluster1: clusterWord) {
        for (auto cluster2: clusterWord) {
            if (cluster1.second != cluster2.second) {
                int dif = distLev(cluster1.first, cluster2.first);
                if (dif < minDif)
                    minDif = dif;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        bool hasWord = false;
        for (auto cuv: clusterWord) {
            if (cuv.second == i) {
                cout << cuv.first << " ";
                hasWord = true;
            }
        }
        if (hasWord) {
            cout << '\n';
        }
    }
    cout << minDif;
}
