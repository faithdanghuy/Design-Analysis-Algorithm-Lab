#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <numeric>
#include <algorithm>
using namespace std;

void outputFile(int distance, const vector<int>& ans){
    ofstream outp("4_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }

    for (const int& i : ans)
        outp << i << " ";
    outp << endl << distance;

    outp.close();
}

struct Path{
    int p1, p2, distance;
};

int calculateDistance(const vector<int>& cities, const vector<Path>& P){
    int dis = 0, n = cities.size();

    // Calculate the distance from the first point to last
    for (int i = 0; i < n - 1; ++i){
        bool valid = false;
        for (const Path& p : P){
            if ((p.p1 == cities[i] && p.p2 == cities[i + 1]) || 
                (p.p2 == cities[i] && p.p1 == cities[i + 1])){
                dis += p.distance;
                valid = true;
                break;
            }
        }
        if (!valid) return INT_MAX;
    }

    bool valid = false;
    // Calculate the distance from the last point back to first
    for (const Path& p : P){
        if ((p.p1 == cities.front() && p.p2 == cities.back()) || 
            (p.p2 == cities.front() && p.p1 == cities.back())){
            dis += p.distance;
            valid = true;
            break;
        }
    }
    if (!valid) return INT_MAX;

    return dis;
}

pair<int, vector<int>> salesman_BruteForce(const vector<Path>& P, int n){
    vector<int> cities(n), minPath;
    int minDis = INT_MAX;

    // Populate the vector with value from 1 to n to create the first permutation
    iota(cities.begin(), cities.end(), 1);

    do {
        int curDis = calculateDistance(cities, P);
        if (curDis < minDis){
            minDis = curDis;
            minPath = cities;
        }
    } while (next_permutation(cities.begin() + 1, cities.end()));

    return {minDis, minPath};
}

int main(){
    int n;

    // Input file
    ifstream inp("4.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<Path> P(n);
    for (int i = 0; i < n; ++i)
        inp >> P[i].p1 >> P[i].p2 >> P[i].distance;
    
    inp.close();

    pair<int, vector<int>> result = salesman_BruteForce(P, n);
    for (int i : result.second)
        cout << i << " ";
    cout << "\nMinimum distance: " << result.first;
    outputFile(result.first, result.second);
}