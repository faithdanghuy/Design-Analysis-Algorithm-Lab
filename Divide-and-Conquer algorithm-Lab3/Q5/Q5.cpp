/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cfloat>
#include <vector>
#include <cmath>
using namespace std;

struct point {
    int x, y;
};

float dist(const point& a, const point& b){
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void print(const pair<float, vector<point>>& ans){
    for (const auto& p : ans.second)
        cout << p.x << "  " << p.y << endl;
    cout << ans.first;
}

pair<float, vector<point>> closestPairBruteForce(const vector<point>& arr){
    float minDist = FLT_MAX;
    vector<point> minPair(2);
    for (int i = 0; i < arr.size(); ++i){
        for (int j = i + 1; j < arr.size(); ++j){
            float d = dist(arr[i], arr[j]);
            if (d < minDist){
                minDist = d;
                minPair[0] = arr[i];
                minPair[1] = arr[j];
            }
        }
    }
    return {minDist, minPair};
}

pair<float, vector<point>> closestPairInStrip(vector<point>& strip, float d) {
    float minDist = d;
    vector<point> minPair(2);

    sort(strip.begin(), strip.end(), [](const point& a, const point& b) { return a.y < b.y; });

    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            float dis = dist(strip[i], strip[j]);
            if (dis < minDist) {
                minDist = dis;
                minPair[0] = strip[i];
                minPair[1] = strip[j];
            }
        }
    }
    return {minDist, minPair};
}

pair<float, vector<point>> closestPair(const vector<point>& arr){
    if (arr.size() <= 3)
        return closestPairBruteForce(arr);

    int mid = arr.size() / 2;
    point midPoint = arr[mid];
    pair<float, vector<point>> left_result, right_result, result, strip_result;

    vector<point> left_arr(arr.begin(), arr.begin() + mid);
    vector<point> right_arr(arr.begin() + mid, arr.end());

    left_result = closestPair(left_arr);
    right_result = closestPair(right_arr);

    result = left_result.first < right_result.first ? left_result : right_result;

    vector<point> strip;
    for (const auto& p : arr){
        if (abs(p.x - midPoint.x) < result.first)
            strip.push_back(p);
    }

    strip_result = closestPairInStrip(strip, result.first);
    if (strip_result.first < result.first)
        result = strip_result;

    return result;
}

int main(){
    int n;
    ifstream inp("5.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }
    inp >> n;
    vector<point> arr(n);
    for (int i = 0; i < n; ++i)
        inp >> arr[i].x >> arr[i].y;
    inp.close();

    // sort the array in ascending order by x-cord
    sort(arr.begin(), arr.end(), [](const point& a, const point& b) { return a.x < b.x; });
    
    print(closestPair(arr));

    return 0;
}