#include <bits/stdc++.h>
#define MAX 131072

using namespace std;
const int NMAX = 11;
const int DIMMASK = (1 << NMAX);

int dp[2][1002];

// dp[i][j] = subsirul de lungime maxima daca am parcurs i elemente din primul sir si j elemente din al doilea

int longestCommonSubsequence(string text1, string text2) {
    int line1 = 1;
    int line2 = 0;
    for(int i = 1; i <= text1.size(); i++){
        for(int j = 1; j <= text2.size(); j++){
            if(text1[i - 1] == text2[j - 1])
                dp[line1][j] = dp[line2][j - 1] + 1;
            else dp[line1][j] = max(dp[line2][j], dp[line1][j - 1]);
        }
        line1 ^= 1;
        line2 ^= 1;
    }

    return dp[line2][text2.size()];
}

int main(){

    int ans = longestCommonSubsequence("bsbininm", "jmjkbkjkv");
    cout << ans;

    return 0;
}
