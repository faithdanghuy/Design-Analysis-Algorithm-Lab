/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The Floyd’s algorithm for the all-pairs shortest-paths problem
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

void printPath(int i, int j, const vector<vector<int>>& next) {
    if (next[i][j] == -1) return;
    int intermediate = next[i][j];
    if (intermediate != j) {
        printPath(i, intermediate, next);
        cout << intermediate + 1 << " - ";
    }
}

void floydWarshall(const vector<vector<int>>& graph, vector<vector<int>>& next, int n) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] != INT_MAX) {
                cout << i + 1 << " - ";
                printPath(i, j, next);
                cout << j + 1 << ": " << to_string(dist[i][j]) << endl;
            }
        }
    }
}


int main(){
    ifstream inp("5.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    int n;
    inp >> n;

    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i){
        int m;
        inp >> m;
        for (int j = 0; j < m; ++j){
            int vertex, weight;
            inp >> vertex >> weight;
            graph[i][vertex - 1] = weight;
            next[i][vertex - 1] = vertex - 1;
        }
        graph[i][i] = 0;
        next[i][i] = i;
    }

    inp.close();

    floydWarshall(graph, next, n);

    return 0;    
}