#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void outputFile(const vector<vector<int>>& ans){
    ofstream outp("5_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }
    for (const auto& subset : ans) {
        for (size_t i = 0; i < subset.size(); ++i) {
            outp << subset[i];
            if (i < subset.size() - 1)
                outp << " ";
        }
        outp << endl;
    }
    outp.close();
}

void sumSubset_BruteForce(const vector<int>& arr, int index, vector<int>& curSubset, int currentSum, int k, vector<vector<int>>& ans){
    if (currentSum == k) {
        ans.push_back(curSubset);
        return;
    }
    if (index == arr.size() || currentSum > k)
        return;

    curSubset.push_back(arr[index]);
    sumSubset_BruteForce(arr, index + 1, curSubset, currentSum + arr[index], k, ans);

    curSubset.pop_back();
    sumSubset_BruteForce(arr, index + 1, curSubset, currentSum, k, ans);
}

int main(){
    int n, k;

    // Input file
    ifstream inp("5.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        inp >> arr[i];
    inp >> k;
    
    inp.close();

    vector<vector<int>> ans;
    vector<int> curSubset;

    sumSubset_BruteForce(arr, 0, curSubset, 0, k, ans);

    if (ans.empty()){
        cout << "No solution" << endl;
        return 1;
    }
    cout << "All susbset with the sum of " << k << endl;
    for (const auto& subset : ans) {
        for (size_t i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1)
                cout << " ";
        }
        cout << endl;
    }
    outputFile(ans);

    return 0;
}