/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The Longest common subsequence (LCS) problem
*/

#include <iostream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

string LCS(const string& S, const string& T){
    int n = S.length();
    int m = T.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (S[i - 1] == T[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1; 
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int i = n, j = m;
    string lcs;
    while (i > 0 && j > 0) {
        if (S[i - 1] == T[j - 1]) {
            lcs = S[i - 1] + lcs;
            --i;
            --j;
        } 
        else if (dp[i - 1][j] > dp[i][j - 1])
            --i;
        else --j;
    }

    return lcs;
}

int main(){
    string S, T;

    cout << "Enter the 2 strings:\n";
    getline(cin, S);
    getline(cin, T);

    cout << LCS(S, T);

    return 0;
}