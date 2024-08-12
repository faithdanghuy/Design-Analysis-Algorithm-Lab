/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/

#include <iostream>
#include <bitset>
using namespace std;

int bitLen(const unsigned int& num){
    return bitset<32>(num).count();
}

int multiplyBits(const unsigned int& x, const unsigned int& y){
    int maxLen = max(bitLen(x), bitLen(y));
    if (maxLen <= 1) return x * y;

    int m = maxLen / 2;

    unsigned int a = x >> m;
    unsigned int b = x & ((1 << m) - 1);
    unsigned int c = y >> m;
    unsigned int d = y & ((1 << m) - 1);

    unsigned int z0 = multiplyBits(b, d);
    unsigned int z2 = multiplyBits(a, c);
    unsigned int z1 = multiplyBits((a + b), (c + d)) - z0 - z2;

    return (z2 << (2*m)) + (z1 << m) + z0;
}

int main(){
    unsigned int x, y;
    cout << "Enter the 2 numbers\n";

    while (true){
        if (cin >> x && x >= 0)
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }

    while (true){
        if (cin >> y && y >= 0)
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }

    cout << multiplyBits(x, y);

    return 0;
}