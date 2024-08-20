/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The change-making problem
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

int changeMaking(const vector<int>& denomination, vector<int>& solution, int target) {
    vector<int> dp(target + 1, INT_MAX);
    vector<int> lastCoin(target + 1, -1);

    dp[0] = 0;

    for (int i = 0; i < denomination.size(); ++i){
        for (int amount = denomination[i]; amount <= target; ++amount){
            if (dp[amount - denomination[i]] != INT_MAX && dp[amount - denomination[i]] + 1 < dp[amount]){
                dp[amount] = dp[amount - denomination[i]] + 1;
                lastCoin[amount] = i;
            }
        }
    }

    if (dp[target] == INT_MAX)
        return -1;

    int amount = target;
    while (amount > 0) {
        int coinIndex = lastCoin[amount];
        solution[coinIndex]++;
        amount -= denomination[coinIndex];
    }

    return dp[target];
}

int main(){
    ifstream inp("2.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int k, n;
    inp >> k;
    vector<int> denomination(k), solution(k, 0);

    for (int i = 0; i < k; ++i)
        inp >> denomination[i];
    inp >> n;
    
    inp.close();

    int minCoin = changeMaking(denomination, solution, n);
    
    if (minCoin == -1) {
        cout << "No solution";
        return 0;
    }
    else{
        for (int i = 0; i < k; ++i)
            cout << denomination[i] << ":" << solution[i] << endl;
    }

    return 0;
}