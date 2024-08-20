/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The Knapsack problem
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct item{
    int weight, value;
};

void knapsack(const vector<item>& arr, int C, int n){
    vector<vector<int>> dp(n + 1, vector<int>(C + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= C; ++w) {
            if (arr[i - 1].weight <= w)
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - arr[i - 1].weight] + arr[i - 1].value);
            else dp[i][w] = dp[i - 1][w];
        }
    }

    int w = C;
    vector<int> chosen_items;
    int total_value = dp[n][C];
    
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            chosen_items.push_back(i);
            w -= arr[i - 1].weight;
        }
    }

    if (total_value > 0) {
        sort(chosen_items.begin(), chosen_items.end());

        for (int i = 0; i < chosen_items.size(); ++i)
            cout << chosen_items[i] << " ";
        cout << endl << total_value << endl;
    } 
    else cout << "No solution" << endl;
}

int main(){
    ifstream inp("9.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int C, n;
    inp >> C;
    inp >> n;
    vector<item> arr(n);
    for (int i = 0; i < n; ++i)
        inp >> arr[i].weight >> arr[i].value;
    
    inp.close();

    knapsack(arr, C, n);

    return 0;
}