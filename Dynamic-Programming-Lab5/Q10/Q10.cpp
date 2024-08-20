/*
Đặng Hà Huy - 21127296
Lab 5: Dynamic Programming

The traveling salesman problem
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

int tsp(int mask, int pos, int n, const vector<vector<int>>& dist, vector<vector<int>>& dp) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int res = INT_MAX;
    for (int city = 0; city < n; ++city) {
        if ((mask & (1 << city)) == 0) {
            int newRes = dist[pos][city] + tsp(mask | (1 << city), city, n, dist, dp);
            res = min(res, newRes);
        }
    }

    return dp[mask][pos] = res;
}

void reconstructPath(vector<int>& path, const vector<vector<int>>& dist, const vector<vector<int>>& dp, int n) {
    int mask = 1, pos = 0;

    path.push_back(pos + 1);
    while (mask != (1 << n) - 1) {
        int nextPos = -1;
        int minDist = INT_MAX;
        for (int city = 0; city < n; ++city) {
            if ((mask & (1 << city)) == 0) {
                int newDist = dist[pos][city] + dp[mask | (1 << city)][city];
                if (newDist < minDist) {
                    minDist = newDist;
                    nextPos = city;
                }
            }
        }
        if (nextPos == -1) break;

        mask |= (1 << nextPos);
        path.push_back(nextPos + 1);
        pos = nextPos;
    }
}

int main() {
    ifstream inp("10.txt");
    if (!inp) {
        cout << "Input fail!" << endl;
        return 1;
    }
    int n;
    inp >> n;

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    int u, v, d;
    while (inp >> u) {
        if (u == -1) break;
        inp >> v >> d;
        dist[u - 1][v - 1] = d;
        dist[v - 1][u - 1] = d;
    }

    inp.close();

    vector<int> path;
    int minCost = tsp(1, 0, n, dist, dp);
    reconstructPath(path, dist, dp, n);

    for (const int& city : path)
        cout << city << " ";
    cout << endl << minCost;

    return 0;
}
