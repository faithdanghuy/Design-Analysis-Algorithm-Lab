#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// define all possible knight moves
const int moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

void outputFile(const vector<vector<int>>& board){
    ofstream oup("2_out.txt");
    if (!oup){
        cout << "Output fail!";
        return;
    }

    for (const auto& row : board){
        for (int cell : row){
            if (cell < 10)
                oup << cell << "  ";
            else oup << cell << " ";
        }
        oup << endl;
    }
    oup.close();
}

void printBoard(const vector<vector<int>>& board){
    for (const auto& row : board){
        for (int cell : row){
            if (cell < 10)
                cout << cell << "  ";
            else cout << cell << " ";
        }
        cout << endl;
    }
}

bool isValid(const vector<vector<int>>& board, int x, int y, int n){
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 0);
}

bool knightTour(vector<vector<int>>& board, int n, int i, int x, int y){
    if (i > n * n)
        return true;

    for (int i = 0; i < 8; ++i){
        int nextX = x + moves[i][0];
        int nextY = y + moves[i][1];

        if (isValid(board, nextX, nextY, n)){
            board[nextX][nextY] = i;
            if (knightTour(board, n, i + 1, nextX, nextY))
                return true;

            board[nextX][nextY] = 0;
        }
    }

    return false;
}

int main(){
    int n, startX, startY;
    ifstream inp("2.txt");
    if (!inp){
        cout << "Input fail!";
        return 1;
    }

    inp >> n;
    inp >> startX >> startY;

    inp.close();

    vector<vector<int>> board(n, vector<int>(n, 0));
    board[startX][startY] = 1;

    if (knightTour(board, n, 2, startX, startY)){
        printBoard(board);
        outputFile(board);
    }
    else cout << "No solution" << endl;

    return 0;
}