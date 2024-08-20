/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The Matrix chain multiplication problem
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

void printOptimalParents(vector<vector<int>>& s, int i, int j) {
    if (i == j)
        cout << "A" << i;
    else {
        cout << "(";
        printOptimalParents(s, i, s[i][j]);
        cout << " ";
        printOptimalParents(s, s[i][j] + 1, j);
        cout << ")";
    }
}

void matrixChainOrder(vector<int>& matrices, int n) {
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    for (int l = 2; l < n; ++l) {
        for (int i = 1; i < n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + matrices[i - 1] * matrices[k] * matrices[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main(){
    ifstream inp("6.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n;
    inp >> n;

    vector<int> matrices(n + 1);

    for (int i = 0; i < n; ++i){
        int r, c;
        inp >> r >> c;
        matrices[i] = r;
        if (i == n - 1)
            matrices[i + 1] = c;
    }

    inp.close();

    matrixChainOrder(matrices, n + 1);

    return 0;
}

