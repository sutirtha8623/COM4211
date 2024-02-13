#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <unordered_map>
#include "board.hpp"
using namespace std;


Board::Board(vector<int> input, int size) {
    n = size;
    data.resize(n); 
    for (int i = 0; i < n; i++) {
        data[i].resize(n);
        for (int j = 0; j < n; j++) {
            int idx = n*i + j;
            data[i][j] = input[idx];
            if (data[i][j] == 0) {
                empty = make_pair(i, j);
            }
        }
    }
    g = 0; f = 0; parent = nullptr;
    move = -1;
}

Board::Board(const Board& b) {
    n = b.n;
    vector<vector<int>> v (n, vector<int>(n));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            v[i][j] = b.data[i][j];
        }
    }
    data = v;
    g = b.g;
    f = b.f;
    parent = b.parent;
    move = b.move;
    empty = make_pair(b.empty.first, b.empty.second);
}

bool Board::operator==(Board& b) {
    if (empty.first != b.empty.first && empty.second != b.empty.second) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
    else if (move == "down" && empty.first == n-1) {
        return false;
    }
    else if (move == "left" && empty.second == 0) {
        return false;
    }
    else if (move == "right" && empty.second == n-1) {
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
        child.move = 0;
        children.push_back(child);
    }
    if (is_valid_move("down")) {
        Board child(parent);
        child.down();
        child.move = 1;
        children.push_back(child);
    }
    if (is_valid_move("left")) {
        Board child(parent);
        child.left();
        child.move = 2;
        children.push_back(child);
    }
    if (is_valid_move("right")) {
        Board child(parent);
        child.right();
        child.move = 3;
        children.push_back(child);
    }
    return children;
}

int Board::h(unordered_map<int, pair<int, int>> goal) {
    int h = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (data[i][j] == 0) continue;
            auto goal_idx = goal[data[i][j]];
            h += abs(goal_idx.first-i) + abs(goal_idx.second-j);
        }
    }
    return h;
}

void Board::print() {
    // if (this == nullptr) cout << "foo";
    switch (move)
    {
    case 0:
        cout <<"----" << "move up" << "----" << endl;
        break;
    case 1:
        cout <<"----" << "move down" << "----" << endl;
        break;
    case 2:
        cout <<"----" << "move left" << "----" << endl;
        break;
    case 3:
        cout <<"----" << "move right" << "----" << endl;
        break;
    default:
        break;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << data[i][j];
        }
        cout << endl;
    }
}