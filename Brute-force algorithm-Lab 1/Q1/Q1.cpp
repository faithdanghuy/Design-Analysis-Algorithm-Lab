#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool allNegative(const vector<int>& arr){
    return all_of(arr.begin(), arr.end(), [](int x) {return x < 0;});
}

void outputFile(int max, const vector<int>& ans){
    ofstream outp("1_out.txt", ios::app);
    if (!outp){
        cout << "Output fail!";
        return;
    }

    for (const int& i : ans)
        outp << i << " ";
    outp << endl << max << endl;

    outp.close();
}

// Brute force version with running time Θ(𝑛^3)
int contiguousSubarray_BruteForce1(const vector<int>& arr, vector<int>& ans) {
    int n = arr.size();
    int start = 0, end = 0;
    int curSum, maxSum = INT_MIN;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            curSum = 0;
            for (int k = i; k <= j; ++k)
                curSum += arr[k];
            if (curSum > maxSum) {
                maxSum = curSum;
                start = i;
                end = j;
            }
        }
    }

    if (maxSum >= 0) {
        for (int i = start; i <= end; ++i)
            ans.push_back(arr[i]);
    }

    return maxSum;
}

// Upgrade version with running time Θ(𝑛^2)
int contiguousSubarray_BruteForce2(const vector<int>& arr, vector<int>& ans){
    int n = arr.size();
    int start = 0, end = 0;
    int curSum, maxSum = INT_MIN;

    for (int i = 0; i < n; ++i){
        curSum = 0;
        for (int j = i; j < n; ++j){
            curSum += arr[j];
            if (curSum > maxSum){
                maxSum = curSum;
                start = i;
                end = j;
            }
        }
    }

    if (maxSum >= 0) {
        for (int i = start; i <= end; ++i)
            ans.push_back(arr[i]);
    }

    return maxSum;
}

// Dynamic programming version with running time Θ(𝑛)
int contiguousSubarray_BruteForce3(const vector<int>& arr, vector<int>& ans) {
    int n = arr.size();
    int start = 0, end = 0, tempStart = 0;
    int maxSum = INT_MIN, curSum = 0;

    for (int i = 0; i < n; ++i) {
        curSum += arr[i];
        if (curSum > maxSum) {
            maxSum = curSum;
            start = tempStart;
            end = i;
        } 
        if (curSum < 0) {
            curSum = 0;
            tempStart = i + 1;
        }
    }

    if (maxSum >= 0) {
        for (int i = start; i <= end; ++i)
            ans.push_back(arr[i]);
    }

    return maxSum;
}

int main(){
    int n;

    // Input file
    ifstream inp("1.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<int> arr(n), ans1, ans2, ans3;
    for (int i = 0; i < n; ++i)
        inp >> arr[i];
    
    inp.close();

    // Check if all value in array is negative    
    if (allNegative(arr)){
        outputFile(0, {});
        cout << "All elements in the array are negative";
        return 1;
    }

    // Method 1: Brute Force Θ(𝑛^3)
    int max1 = contiguousSubarray_BruteForce1(arr, ans1);
    cout << "\nBrute Force Θ(n^3) method result:" << endl;
    for (const int& i : ans1)
        cout << i << " ";
    cout << endl << max1;
    outputFile(max1, ans1);

    // Method 2: Brute Force Θ(𝑛^2)
    int max2 = contiguousSubarray_BruteForce2(arr, ans2);
    cout << "\nBrute Force Θ(n^2) method result:" << endl;
    for (const int& i : ans2)
        cout << i << " ";
    cout << endl << max1;
    outputFile(max2, ans2);

    // Method 3: Dynamic programming Θ(𝑛)
    int max3 = contiguousSubarray_BruteForce3(arr, ans3);
    cout << "\nDynamic programming Θ(n) method result:" << endl;
    for (const int& i : ans3)
        cout << i << " ";
    cout << endl << max1;
    outputFile(max3, ans3);
    
    return 0;
}