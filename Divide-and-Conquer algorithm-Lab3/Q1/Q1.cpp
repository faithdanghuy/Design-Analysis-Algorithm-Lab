/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

bool checkDigit(const string& num){
    return all_of(num.begin(), num.end(), ::isdigit);
}

string addString(string u, string v){
    string result;
    int carry = 0, len1 = u.length(), len2 = v.length();
    int maxDigit = max(len1, len2);

    for (int i = 0; i < maxDigit; ++i){
        int digit1 = i < len1 ? u[len1 - 1 - i] - '0' : 0;
        int digit2 = i < len2 ? v[len2 - 1 - i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    if (carry)
        result.push_back(carry + '0');
    reverse(result.begin(), result.end());

    return result;
}

string subtractString(string u, string v) {
    string result;
    int borrow = 0;
    int len1 = u.length(), len2 = v.length();

    for (int i = 0; i < len1; ++i) {
        int digit1 = u[len1 - 1 - i] - '0';
        int digit2 = i < len2 ? v[len2 - 1 - i] - '0' : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;

        result.push_back(diff + '0');
    }

    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    reverse(result.begin(), result.end());

    return result;
}

string karatsuba(string u, string v){
    int len1 = u.length(), len2 = v.length();

    if (len1 == 1 && len2 == 1)
        return to_string((u[0] - '0') * (v[0] - '0'));

    if (len1 < len2) u.insert(u.begin(), len2 - len1, '0');
    else if (len2 < len1) v.insert(v.begin(), len1 - len2, '0');

    int m = u.length() / 2;

    string a = u.substr(0, u.length() - m);
    string b = u.substr(u.length() - m);
    string c = v.substr(0, v.length() - m);
    string d = v.substr(v.length() - m);

    string z0 = karatsuba(b, d);
    string z2 = karatsuba(a, c);

    string z1 = karatsuba(addString(a, b), addString(c, d));
    z1 = subtractString(subtractString(z1, z2), z0);
    
    string result = addString(addString(z2.append(2*m, '0'), z1.append(m, '0')), z0);

    return result.erase(0, result.find_first_not_of('0'));
}

int main(){
    string u, v;
    cout << "Enter the 2 numbers\n";

    while (true){
        if (getline(cin, u) && checkDigit(u))
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }

    while (true){
        if (getline(cin, v) && checkDigit(v))
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }

    cout << karatsuba(u, v);

    return 0;
}