/*
Đặng Hà Huy - 21127296
Lab 4: Decrease and Conquer
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int kSmallest(const vector<int>& arr, int start, int end, int k){
    if (k <= 0 || start > end || k > end - start + 1){
        cout << "Invalid array or k!";
        exit(0);
    }

    if (end - start + 1 <= k){
        vector<int> segment(arr.begin() + start, arr.begin() + end + 1);
        return segment[k - 1];
    }

    int mid = (start + end) / 2;
    int left = mid - start + 1;

    if (k <= left)
        return kSmallest(arr, start, mid, k);
    else return kSmallest(arr, mid + 1, end, k - left);
}

int main(){
    int n, k;
    ifstream inp("3.txt");
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

    cout << kSmallest(arr, 0, n - 1, k);

    return 0;
}