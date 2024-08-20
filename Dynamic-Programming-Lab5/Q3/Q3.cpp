/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The Longest monotonically increasing subsequence (LMIS) problem
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int LMIS(const vector<int>& arr, vector<int>& result){
    int n = arr.size();
    if (n == 0)
        return 0;

    vector<int> dp(n, 1);
    vector<int> prevNum(n, -1);
    int maxIndex = 0;

    for (int i = 1; i < n; ++i){
        for (int prev = 0; prev < i; ++prev){
            if (arr[prev] < arr[i] && dp[i] < dp[prev] + 1){
                dp[i] = dp[prev] + 1;
                prevNum[i] = prev;
            }
        }
        if (dp[i] > dp[maxIndex])
            maxIndex = i;
    }

    result.clear();
    for (int i = maxIndex; i != -1; i = prevNum[i])
        result.push_back(arr[i]);
    
    reverse(result.begin(), result.end());

    return dp[maxIndex];
}

int main(){
    ifstream inp("3.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n;
    inp >> n;
    
    vector<int> arr(n), result;
    for (int i = 0; i < n; ++i)
        inp >> arr[i];

    inp.close();

    int lmisLen = LMIS(arr, result);

    for (const int& i : result)
        cout << i << " ";

    return 0;
}