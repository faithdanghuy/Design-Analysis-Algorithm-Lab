#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Maze {
    int w, h;
    pair<int, int> start;
    pair<int, int> goal;
    vector<vector<char>> layout;
};

void readFile(const string& filename, Maze& maze){
    ifstream inp(filename);
    if (!inp){
        cout << "Input fail!";
        return;
    }

    inp >> maze.w >> maze.h;
    inp >> maze.start.first >> maze.start.second;
    inp >> maze.goal.first >> maze.goal.second;
    inp.ignore();
    
    string line;

    while (getline(inp, line)){
        vector<char> row;
        for (const char& c : line)
            row.push_back(c);
        maze.layout.push_back(row);
    }
    inp.close();
}

void outputFile(const vector<vector<char>>& maze){
    ofstream oup("3_out.txt");
    if (!oup){
        cout << "Output fail!";
        return;
    }

    for (const auto& row : maze){
        for (const char& cell : row)
            oup << cell << " ";
        oup << endl;
    }
    oup.close();
}

void printBoard(const vector<vector<char>>& maze){
    for (const auto& row : maze){
        for (const char& cell : row)
            cout << cell << " ";
        cout << endl;
    }
}

bool Find_Path(vector<vector<char>>& maze, int r, int c, int w, int h){
    if (r < 0 || r >= h || c < 0 || c >= w)
        return false;
    if (maze[r][c] == 'G')
        return true;
    if (maze[r][c] == '#' || maze[r][c] == 'X')
        return false;

    if (maze[r][c] != 'S')
        maze[r][c] = 'X';

    if (Find_Path(maze, r - 1, c, w, h))
        return true;
    if (Find_Path(maze, r, c + 1, w, h))
        return true;
    if (Find_Path(maze, r + 1, c, w, h))
        return true;
    if (Find_Path(maze, r, c - 1, w, h))
        return true;

    if (maze[r][c] != 'S')
        maze[r][c] = ' ';
    return false;
}

int main(){
    Maze maze;
    readFile("3.txt", maze);

    if (Find_Path(maze.layout, maze.start.second, maze.start.first, maze.w, maze.h)){
        printBoard(maze.layout);
        outputFile(maze.layout);
    }
    else cout << "No solution" << endl;

    return 0;
}