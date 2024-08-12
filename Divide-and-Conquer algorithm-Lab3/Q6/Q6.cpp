/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct coin {
    int value, num = 0;
};

void changeMaking(int n, vector<coin>& coinsArr) {
    if (n <= 0) return;

	for (coin& c : coinsArr) {
		if (n >= c.value) {
			c.num++;
			changeMaking(n - c.value, coinsArr);
            break;
		}
	}
}

int main() {
    int k, n;
    ifstream inp("6.txt");
    if (!inp) {
        cout << "Input fail!";
        return 1;
    }

    inp >> k;
    vector<coin> coinsArr(k);
    for (int i = 0; i < k; ++i)
        inp >> coinsArr[i].value;
    inp >> n;
    inp.close();

    changeMaking(n, coinsArr);

    for (const coin& c : coinsArr)
        cout << c.value << ":" << c.num << endl;

    return 0;
}
