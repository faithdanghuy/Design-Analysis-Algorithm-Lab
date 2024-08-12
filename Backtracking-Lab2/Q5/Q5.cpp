#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void outputFile(const vector<int>& path){
    ofstream oup("5_out.txt");
    if (!oup){
        cout << "Output fail!";
        return;
    }

    for (const int& num : path)
        oup << num << " ";
    oup << endl;
    oup.close();
}

bool promising(const vector<vector<int>>& G, vector<int>& path, int pos, int v, int n){
    if (pos == n - 1 && G[v][path[0]] == 0)
        return false;
    else {
        if (G[path[pos - 1]][v] == 0)
            return false;
        else {
            for (int i = 0; i < pos - 1; ++i){
                if (path[i] == v)
                    return false;
            }
        }
    }
    return true;
}

void hamiltionian(const vector<vector<int>>& G, vector<int>& path, int pos, int n){
    if (pos == n){
        for (const int& v : path)
            cout << v << " ";
        exit(1);
    }
    else {
        for (int v = 0; v < n; ++v){
            if (promising(G, path, pos, v, n)){
                path[pos] = v;
                hamiltionian(G, path, pos + 1, n);
            }
        }
    }
}

int main(){
    int n, k;
    ifstream inp("5.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<vector<int>> G(n, vector<int>(n));
    vector<int> path(n, -1);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            inp >> G[i][j];
    }
    
    inp >> k;
    inp.close();
    path[0] = k;

    hamiltionian(G, path, 1, n);
    outputFile(path);
    return 0;
}