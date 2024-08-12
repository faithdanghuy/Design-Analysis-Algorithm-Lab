#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<char>>& board){
    for (const auto& row : board){
        for (const char& cell : row)
            cout << cell << " ";
        cout << endl;
    }
    cout << endl;
}

bool isValid(const vector<vector<char>>& board, int row, int col, int n){
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q')
            return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q')
            return false;
    }

    for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;
}

bool NQueen(vector<vector<char>>& board, int row, int n){
    if (row >= n)
        return true;

    for (int col = 0; col < n; ++col){
        if (isValid(board, row, col, n)){
            board[row][col] = 'Q';

        if (NQueen(board, row + 1, n))
            return true;

        board[row][col] = '-';
        }
    }

    return false;
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<vector<char>> board (n, vector<char>(n, '-'));
    if (NQueen(board, 0, n))
        printBoard(board);
    else cout << "No Solution!";
    
    return 0;
}