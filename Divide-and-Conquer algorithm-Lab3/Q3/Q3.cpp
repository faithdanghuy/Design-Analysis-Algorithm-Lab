/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

bool allNegative(const vector<int>& arr){
    return all_of(arr.begin(), arr.end(), [](int x) { return x < 0; });
}

int max3Nums(int a, int b, int c, int& maxIndex){
    if (a >= b && a >= c) {
        maxIndex = 0;
        return a;
    } else if (b >= a && b >= c) {
        maxIndex = 1;
        return b;
    } else {
        maxIndex = 2;
        return c;
    }
}

int subarrayLargestSumCrossing(const vector<int>& arr, int left, int mid, int right, int& crossStart, int& crossEnd) {
    int sum = 0; 
    int left_sum = INT_MIN; 
    int leftIndex = mid;

    for (int i = mid; i >= left; --i) { 
        sum += arr[i]; 
        if (sum > left_sum) {
            left_sum = sum; 
            leftIndex = i;
        }
    } 
  
    sum = 0; 
    int right_sum = INT_MIN; 
    int rightIndex = mid;

    for (int i = mid + 1; i <= right; ++i) { 
        sum += arr[i]; 
        if (sum > right_sum) {
            right_sum = sum; 
            rightIndex = i;
        }
    }

    crossStart = leftIndex;
    crossEnd = rightIndex;

    int crossSum = left_sum + right_sum;
    return crossSum;
}

int subarrayLargestSum(const vector<int>& arr, int left, int right, int& start, int& end) {
    if (left > right)
        return INT_MIN;

    if (left == right) {
        start = end = left;
        return arr[left];
    }

    int mid = (left + right) / 2;

    int leftStart, leftEnd, rightStart, rightEnd, crossStart, crossEnd;

    int leftSum = subarrayLargestSum(arr, left, mid - 1, leftStart, leftEnd);
    int rightSum = subarrayLargestSum(arr, mid + 1, right, rightStart, rightEnd);
    int crossSum = subarrayLargestSumCrossing(arr, left, mid, right, crossStart, crossEnd);

    int maxIndex;
    int maxSum = max3Nums(leftSum, rightSum, crossSum, maxIndex);

    if (maxIndex == 0) {
        start = leftStart;
        end = leftEnd;
    } else if (maxIndex == 1) {
        start = rightStart;
        end = rightEnd;
    } else {
        start = crossStart;
        end = crossEnd;
    }

    return maxSum;
}

int main(){
    int n;
    ifstream inp("3.txt");
    if (!inp){
        cout << "Input fail!" << endl;
        return 1;
    }
    inp >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        inp >> arr[i];
    inp.close();

    if (allNegative(arr)){
        cout << "All elements in the array are negative!\n0";
        return 2;
    }

    int start = 0, end = 0;
    int maxSum = subarrayLargestSum(arr, 0, arr.size() - 1, start, end);

    for (int i = start; i <= end; ++i)
        cout << arr[i] << " ";
    cout << endl << maxSum;

    return 0;
}
