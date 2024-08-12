#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <numeric>
#include <algorithm>
using namespace std;

void outputFile(const vector<int>& ans, int minCost, int n){
    ofstream outp("7_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }

    for (int i = 0; i < n; ++i)
        outp << ans[i] << " ";
    outp << endl << minCost;

    outp.close();
}

int calculateCost(const vector<int>& assign, const vector<vector<int>>& jobCost){
    int totalCost = 0;
    for (int i = 0; i < assign.size(); ++i)
        totalCost += jobCost[i][assign[i] - 1];

    return totalCost;
}

pair <vector<int>, int> assignment_BruteForce(const vector<vector<int>>& jobCost, int n){
    vector<int> assign(n), minAssign(n);
    int minCost = INT_MAX;
    
    // Populate the vector with value from 1 to n to create the first permutation
    iota(assign.begin(), assign.end(), 1);

    do {
        int curCost = calculateCost(assign, jobCost);
        if (curCost < minCost){
            minCost = curCost;
            minAssign = assign;
        }
    } while (next_permutation(assign.begin(), assign.end()));

    return {minAssign, minCost};
}

int main(){
    int n;

    // Input file
    ifstream inp("7.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<vector<int>> jobCost(n, vector<int>(n));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            inp >> jobCost[i][j];
        }
    }
    inp.close();

    pair<vector<int>, int> result = assignment_BruteForce(jobCost, n);
    for (int i : result.first)
        cout << i << " ";
    cout << "\nMinimum cost: " << result.second;
    outputFile(result.first, result.second, n);
}