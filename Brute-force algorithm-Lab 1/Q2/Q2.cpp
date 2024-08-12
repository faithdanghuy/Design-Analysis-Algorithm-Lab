#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <climits>
using namespace std;

void outputFile(const vector<int>& arr, const vector<int>& ans){
    ofstream outp("2_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }
    for (int i = 0; i < arr.size(); ++i)
        outp << arr[i] << ":" << ans[i] << endl;
    outp.close();
}

void changeMaking_BruteForce(const vector<int>& arr, vector<int>& ans, vector<int>& temp, int& minCoins, int curValue, int goal, int index){
    if (curValue == goal) {
        int numCoins = accumulate(temp.begin(), temp.end(), 0);
        if (numCoins < minCoins) {
            minCoins = numCoins;
            ans = temp;
        }
        return;
    }
    
    if (curValue > goal || index == arr.size()) 
        return;

    temp[index]++;
    changeMaking_BruteForce(arr, ans, temp, minCoins, curValue + arr[index], goal, index);

    temp[index]--;
    changeMaking_BruteForce(arr, ans, temp, minCoins, curValue, goal, index + 1);
}

int main(){
    int k, goal, minCoins = INT_MAX;

    // Input file
    ifstream inp("2.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> k;
    vector<int> arr(k), coinArr(k, 0), temp(k, 0);
    for (int i = 0; i < k; ++i)
        inp >> arr[i];
    inp >> goal;
    
    inp.close();

    changeMaking_BruteForce(arr, coinArr, temp, minCoins, 0, goal, 0);

    if (minCoins == INT_MAX){
        cout << "No Solution";
        return 1;
    }
    for (int i = 0; i < k; ++i)
        cout << arr[i] << ":" << coinArr[i] << endl;
    outputFile(arr, coinArr);
    
    return 0;
}