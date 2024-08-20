/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The sum of subsets problem
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void sumSubset(const vector<int>& arr, int n, int k){
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
    vector<vector<vector<int>>> subsets(n + 1, vector<vector<int>>(k + 1));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= k; ++j){
            if (arr[i - 1] > j){
                dp[i][j] = dp[i - 1][j];
                subsets[i][j] = subsets[i - 1][j];               
            }
            else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
                
                if (dp[i - 1][j])
                    subsets[i][j] = subsets[i - 1][j];
                
                if (dp[i - 1][j - arr[i - 1]]) {
                    vector<int> tempSubset = subsets[i - 1][j - arr[i - 1]];
                    tempSubset.push_back(arr[i - 1]);
                    subsets[i][j] = tempSubset;
                }
            }
        }
    }

    if (dp[n][k]) {
        for (const int& i : subsets[n][k])
            cout << i << " ";
    } 
    else cout << "No solution";
}

int main(){
    ifstream inp("8.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n, k;
    inp >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        inp >> arr[i];
    inp >> k;
    inp.close();

    sumSubset(arr, n, k);

    return 0;
}