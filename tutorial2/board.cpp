#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>
#include "board.hpp"
using namespace std;

Board::Board(vector<int> input) {
    board.resize(4); 
    for (int i = 0; i < 4; i++) {
        board[i].resize(4);
        for (int j = 0; j < 4; j++) {
            int idx = 4*i + j;
            board[i][j] = input[idx];
            if (board[i][j] == 0) {
                empty = make_pair(i, j);
            }
        }
    }
}

Board::Board(Board& b) {
    vector<vector<int>> v (4, vector<int>(4));
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j++) {
            v[i][j] = b.board[i][j];
        }
    }
    board = v;
    empty = make_pair(b.empty.first, b.empty.second);
}

void Board::up() {
    int i = empty.first;
    int j = empty.second;

    board[i][j] = board[i-1][j];
    board[i-1][j] = 0;

    empty = make_pair(i-1, j);
    
}

void Board::down() {
    int i = empty.first;
    int j = empty.second;

    board[i][j] = board[i+1][j];
    board[i+1][j] = 0;

    empty = make_pair(i+1, j);
    
}

void Board::left() {
    int i = empty.first;
    int j = empty.second;

    board[i][j] = board[i][j-1];
    board[i][j-1] = 0;
    
    empty = make_pair(i, j-1);
}

void Board::right() {
    int i = empty.first;
    int j = empty.second;

    board[i][j] = board[i][j+1];
    board[i][j+1] = 0;
    
    empty = make_pair(i, j+1);
}

int Board::h(unordered_map<int, pair<int, int>> goal) {
    int h = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auto goal_idx = goal[board[i][j]];
            h += abs(goal_idx.first-i) + abs(goal_idx.second-j);
        }
    }
    return h;
}

void Board::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(3) << board[i][j];
        }
        cout << endl;
    }
}