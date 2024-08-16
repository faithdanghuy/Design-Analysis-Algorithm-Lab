/*
Đặng Hà Huy - 21127296
Lab 4: Decrease and Conquer
*/

#include <iostream>
using namespace std;

// k = 2 as in eliminate every second person
int josephus(int n, int k = 2){
    int survivor = 0;

    for (int i = 2; i <= n; ++i)
        survivor = (survivor + k) % i;

    return survivor + 1;
}

int main() {
    int n;
    while (true){
        if (cin >> n && n > 2)
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }

    cout << josephus(n);
    return 0;
}