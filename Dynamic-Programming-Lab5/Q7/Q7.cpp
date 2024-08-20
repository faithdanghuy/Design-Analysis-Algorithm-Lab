/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The optimal binary search trees
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;

pair<vector<int>, double> optimalBST(const vector<int>& keys, const vector<double>& probs) {
    int n = keys.size();
    vector<vector<double>> cost(n, vector<double>(n, 0));
    vector<vector<double>> sumProb(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        sumProb[i][i] = probs[i];
        cost[i][i] = probs[i];
    }

    for (int L = 2; L <= n; ++L) {
        for (int i = 0; i <= n - L; ++i) {
            int j = i + L - 1;
            sumProb[i][j] = sumProb[i][j - 1] + probs[j];
            cost[i][j] = numeric_limits<double>::max();

            for (int r = i; r <= j; ++r) {
                double c = ((r > i) ? cost[i][r - 1] : 0) +
                           ((r < j) ? cost[r + 1][j] : 0) +
                           sumProb[i][j];
                if (c < cost[i][j])
                    cost[i][j] = c;
            }
        }
    }

    vector<int> optimalKeys;
    for (int i = 0; i < n; ++i)
        optimalKeys.push_back(keys[i]);

    return {optimalKeys, cost[0][n - 1]};
}

int main(){
    ifstream inp("7.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n;
    inp >> n;

    vector<int> keys(n);
    vector<double> probs(n);

    for (int i = 0; i < n; ++i)
        inp >> keys[i];

    for (int i = 0; i < n; ++i)
        inp >> probs[i];

    inp.close();

    auto result = optimalBST(keys, probs);

    for (int i = 0; i < n; ++i)
        cout << result.first[i] << " " << probs[i] << endl;
    cout << result.second;

    return 0;
}