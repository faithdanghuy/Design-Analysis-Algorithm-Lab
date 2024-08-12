#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point{
    int x, y;
};

void outputFile(const vector<Point>& points){
    ofstream outp("3_out.txt");
    if (!outp){
        cout << "Output fail!";
        return;
    }

    for (const Point& p : points)
        outp << p.x << " " << p.y << endl;

    outp.close();
}

float computeAngle(Point a, Point b){
    float angle = atan2(b.y - a.y, b.x - a.x);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

pair<float, Point> findNextExtremePoint(const vector<Point>& points, Point cur, float curAngle){
    float minAngle = 2 * M_PI;
    Point next = cur;

    for (const Point& p : points){
        if (p.x == cur.x && p.y == cur.y)
            continue;
        float angle = computeAngle(cur, p);
        if (angle >= curAngle && angle < minAngle) {
            next = p;
            minAngle = angle;
        }
    }

    return {minAngle, next};
}

vector<Point> convexHull_BruteForce(const vector<Point>& points){
    vector<Point> hull;
    // Find the leftmost point
    Point first = *min_element(points.begin(), points.end(), [](Point a, Point b){
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
    });
    hull.push_back(first);
    float curAngle = 0;
    Point cur = first;

    while (true){
        pair<float, Point> result = findNextExtremePoint(points, cur, curAngle);
        if (first.x == result.second.x && first.y == result.second.y) 
            break;
        hull.push_back(result.second);
        cur = result.second;
        curAngle = result.first;
    }

    return hull;
}

int main(){
    int n;

    // Input file
    ifstream inp("3.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i)
        inp >> points[i].x >> points[i].y;
    inp.close();

    vector<Point> convexHull = convexHull_BruteForce(points);

    for (const Point& p : convexHull)
        cout << p.x << " " << p.y << endl;
    outputFile(convexHull);
}