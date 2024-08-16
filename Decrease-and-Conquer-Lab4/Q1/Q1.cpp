/*
Đặng Hà Huy - 21127296
Lab 4: Decrease and Conquer
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topologicalSort(const vector<vector<int>>& adjList, int n) {
    vector<int> inDegree(n + 1, 0);
    vector<int> topOrder;
    queue<int> zeroInDegreeQueue;

    for (int i = 1; i <= n; ++i) {
        for (int j : adjList[i]) {
            inDegree[j]++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            zeroInDegreeQueue.push(i);
        }
    }

    while (!zeroInDegreeQueue.empty()) {
        int u = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        topOrder.push_back(u);

        for (int v : adjList[u]) {
            if (--inDegree[v] == 0) {
                zeroInDegreeQueue.push(v);
            }
        }
    }

    if (topOrder.size() != n)
        cout << "The graph contains a cycle!" << endl;

    return topOrder;
}

int main(){
    int n;
    ifstream inp("1.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    inp >> n;
    vector<vector<int>> adj(n + 1);
    string line;
    getline(inp, line);

    for (int i = 1; i <= n; ++i){
        getline(inp, line);
        istringstream iss(line);

        int num;
        iss >> num;

        adj[i] = vector<int>(num);
        for (int j = 0; j < num; ++j){
            iss >> adj[i][j];
        }
    }

    inp.close();

    vector<int> result = topologicalSort(adj, n);

    for (int i = 0; i < result.size(); ++i)
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    cout << endl;

    return 0;
}