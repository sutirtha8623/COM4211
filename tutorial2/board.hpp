#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;

class Board {
    vector<vector<int>> board;
    pair<int, int> empty;   
public:
    Board(vector<int>);
    Board(Board&);
    int get(int i, int j) {return board[i][j];}
    pair<int, int> get_empty() {return empty;}
    void up();
    void down();
    void right();
    void left();
    int h(unordered_map<int, pair<int, int>>);
    void print();
};


#endif