/*
Đặng Hà Huy - 21127296
Lab 3: Divide and Conquer
*/

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix;

void printMatrix(const matrix& m){
    for (const auto& row : m){
        for (const int& num : row){
            cout << num << " ";
        }
        cout << "\n";
    }
}

matrix add(const matrix& A, const matrix& B){
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

matrix subtract(const matrix& A, const matrix& B){
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    }
    return C;
}

matrix strassens(const matrix& A, const matrix& B){
    int n = A.size();
    if (n == 1){
        matrix C(n, vector<int>(n));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    matrix A11(newSize, vector<int>(newSize));
    matrix A12(newSize, vector<int>(newSize));
    matrix A21(newSize, vector<int>(newSize));
    matrix A22(newSize, vector<int>(newSize));
    matrix B11(newSize, vector<int>(newSize));
    matrix B12(newSize, vector<int>(newSize));
    matrix B21(newSize, vector<int>(newSize));
    matrix B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    matrix M1 = strassens(add(A11, A22), add(B11, B22));
    matrix M2 = strassens(add(A21, A22), B11);
    matrix M3 = strassens(A11, subtract(B12, B22));
    matrix M4 = strassens(A22, subtract(B21, B11));
    matrix M5 = strassens(add(A11, A12), B22);
    matrix M6 = strassens(subtract(A21, A11), add(B11, B12));
    matrix M7 = strassens(subtract(A12, A22), add(B21, B22));

    matrix C11 = add(subtract(add(M1, M4), M5), M7);
    matrix C12 = add(M3, M5);
    matrix C21 = add(M2, M4);
    matrix C22 = add(add(subtract(M1, M2), M3), M6);

    matrix C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

int main(){
    int n;
    while(true){
        if (cin >> n && n >= 2 && n % 2 == 0)
            break;
        cout << "Invalid input!\n";
        cin.clear();
    }
    matrix A(n, vector<int>(n));
    matrix B(n, vector<int>(n));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cin >> B[i][j];
    }

    printMatrix(strassens(A, B));
    return 0;
}