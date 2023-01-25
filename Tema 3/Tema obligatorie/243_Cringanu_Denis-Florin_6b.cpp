#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 11;
const int DIMMASK = (1 << NMAX);

int dp[1002][1002];

// dp[i][j] = subsirul de lungime maxima daca adaug elementul i din primul sir si am parcurs j elemenete din al doilea
// sirurile de la dreapta la stanga si adaug in raspuns daca valorile celor doua coincid, iar daca nu, ma uit la dinamica
// si selectez dintre caracterul i si j, valoare unde dp[i][j - 1] sau dp[j - 1][i] este mai mare

string shortestCommonSupersequence(string str1, string str2) {
    int length1 = str1.size();
    int length2 = str2.size();
    for(int i = 1; i <= length1; i++){
        for(int j = 1; j <= length2; j++){
            if(str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string ans;

    while(length1 > 0 && length2 > 0){
        if(str1[length1 - 1] == str2[length2 - 1]){
            ans += str1[length1 - 1];
            length1--;
            length2--;
        } else {
            if(dp[length1][length2 - 1] > dp[length1 - 1][length2]){
                ans += str2[length2 - 1];
                length2--;
            } else {
                ans += str1[length1 - 1];
                length1--;
            }
        }
    }

    while(length1 > 0){
        ans += str1[length1 - 1];
        length1--;
    }

    while(length2 > 0){
        ans += str2[length2 - 1];
        length2--;
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int main(){

    string ans = shortestCommonSupersequence("abac", "cab");
    cout << ans;

    return 0;
}
