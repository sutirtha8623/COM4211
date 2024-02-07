#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>
#include "board.hpp"
using namespace std;


Board::Board(vector<int> input) {
    data.resize(4); 
    for (int i = 0; i < 4; i++) {
        data[i].resize(4);
        for (int j = 0; j < 4; j++) {
            int idx = 4*i + j;
            data[i][j] = input[idx];
            if (data[i][j] == 0) {
                empty = make_pair(i, j);
            }
        }
    }
    g = 0; f = 0; parent = nullptr;
}

Board::Board(const Board& b) {
    vector<vector<int>> v (4, vector<int>(4));
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j++) {
            v[i][j] = b.data[i][j];
        }
    }
    data = v;
    empty = make_pair(b.empty.first, b.empty.second);
}

bool Board::operator==(Board& b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (data[i][j] != b.data[i][j]) return false;
        }
    }
    return true;
}

void Board::up() {
    int i = empty.first;
    int j = empty.second;

    data[i][j] = data[i-1][j];
    data[i-1][j] = 0;

    empty = make_pair(i-1, j);
    
}

void Board::down() {
    int i = empty.first;
    int j = empty.second;

    data[i][j] = data[i+1][j];
    data[i+1][j] = 0;

    empty = make_pair(i+1, j);
    
}

void Board::left() {
    int i = empty.first;
    int j = empty.second;

    data[i][j] = data[i][j-1];
    data[i][j-1] = 0;
    
    empty = make_pair(i, j-1);
}

void Board::right() {
    int i = empty.first;
    int j = empty.second;

    data[i][j] = data[i][j+1];
    data[i][j+1] = 0;
    
    empty = make_pair(i, j+1);
}

bool Board::is_valid_move(string move) {
    if (move == "up" && empty.first == 0) {
        return false;
    }
    else if (move == "down" && empty.first == 3) {
        return false;
    }
    else if (move == "left" && empty.second == 0) {
        return false;
    }
    else if (move == "right" && empty.second == 3) {
        return false;
    }
    else {
        return true;
    }
}

vector<Board> Board::generate_children() {
    vector<Board> children;
    Board parent = *this;
    if (is_valid_move("up")) {
        Board child(parent);
        child.up();
        children.push_back(child);
    }
    if (is_valid_move("down")) {
        Board child(parent);
        child.down();
        children.push_back(child);
    }
    if (is_valid_move("left")) {
        Board child(parent);
        child.left();
        children.push_back(child);
    }
    if (is_valid_move("right")) {
        Board child(parent);
        child.right();
        children.push_back(child);
    }
    return children;
}

int Board::h(unordered_map<int, pair<int, int>> goal) {
    int h = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auto goal_idx = goal[data[i][j]];
            h += abs(goal_idx.first-i) + abs(goal_idx.second-j);
        }
    }
    return h;
}

void Board::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(3) << data[i][j];
        }
        cout << endl;
    }
}