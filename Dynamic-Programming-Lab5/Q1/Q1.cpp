/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The problem of maximum sum of a path in a right number triangle
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

pair<int, vector<int>> maxSumTriagle(const vector<vector<int>>& triangle){
    int n = triangle.size();
    
    vector<int> dp = triangle[n - 1];
    vector<vector<int>> path(n, vector<int>(n, -1));

    for (int row = n - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            if (dp[col] > dp[col + 1]) {
                dp[col] = triangle[row][col] + dp[col];
                path[row][col] = col;
            } 
            else {
                dp[col] = triangle[row][col] + dp[col + 1];
                path[row][col] = col + 1;
            }
        }
    }
    
    vector<int> maxPath;
    int col = 0;
    for (int row = 0; row < n; ++row) {
        maxPath.push_back(triangle[row][col]);
        col = path[row][col];
    }

    return {dp[0], maxPath};
}

int main(){
    ifstream inp("1.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n;
    inp >> n;
    inp.ignore();

    vector<vector<int>> triangle(n);

    for (int i = 0; i < n; ++i){
        string line;
        getline(inp, line);
        istringstream iss(line);

        int num;
        while(iss >> num)
            triangle[i].push_back(num);
    }

    inp.close();

    auto result = maxSumTriagle(triangle);
    for (const int& i : result.second)
        cout << i << " ";
    cout << endl << result.first;

    return 0;
}