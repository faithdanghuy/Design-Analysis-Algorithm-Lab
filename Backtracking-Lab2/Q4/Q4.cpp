#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void outputFile(const vector<vector<int>>& ans){
    ofstream oup("4_out.txt");
    if (!oup){
        cout << "Output fail!";
        return;
    }

    for (const auto& subset : ans){
        for (const int& num : subset)
            oup << num << " ";
        oup << endl;
    }

    oup.close();
}

void sumSubset(const vector<int>& w, int size, int sum, int k, int start, vector<int>& s, int n, vector<vector<int>>& ans){
    if (sum == k){
        for (int i = 0; i < size; ++i){
            if (i > 0) cout << " ";
            cout << s[i];
        }
        s.pop_back();
        ans.push_back(s);
        cout << endl;
    }
    else {
        for (int i = start; i < n; i++) {
            s[size] = w[i];
            sumSubset(w, size + 1, sum + w[i], k, i + 1, s, n, ans);
        }  
    }
}


void sumSubset_upgraded(const vector<int>& w, int size, int sum, int k, int start, vector<int>& s, int n, vector<vector<int>>& ans, int total) {
    if (sum == k) {
        for (int i = 0; i < size; i++) {
            if (i > 0) cout << " ";
            cout << s[i];
        }
        s.pop_back();
        ans.push_back(s);
        cout << endl;
    } 
    else {
        int lost = 0;
        for (int i = start; i < n; i++) {
            if ((sum + total - lost >= k) && (sum + w[i] <= k)) {
                s[size] = w[i];
                sumSubset_upgraded(w, size + 1, sum + w[i], k, i + 1, s, n, ans, total - lost - w[i]);
            }
            lost += w[i];
        }
    }
}

int main(){
    int n, k;
    ifstream inp("4.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<int> w(n), s(n);
    for (int i = 0; i < n; ++i)
        inp >> w[i];
    
    inp >> k;
    inp.close();

    vector<vector<int>> ans1, ans2;

    int total = accumulate(w.begin(), w.end(), 0);

    // if (*min_element(w.begin(), w.end()) <= k && k <= total){
    //     sumSubset(w, 0, 0, k, 0, s, n, ans1);
    //     outputFile(ans1);
    // }
    if (w[0] <= k && k <= total){
        sumSubset_upgraded(w, 0, 0, k, 0, s, n, ans2, total);
        outputFile(ans2);
    }

    else cout << "No solution" << endl;
}
