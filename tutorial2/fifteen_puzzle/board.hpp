#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
using namespace std;


class Board {
public:
    vector<vector<int>> data;
    pair<int, int> empty;
    int g, f, n;
    Board* parent;

    Board(vector<int>, int);
    Board(const Board&);
    bool operator== (Board& b);

    int get_data(int i, int j) {return data[i][j];}
    pair<int, int> get_empty() {return empty;}
    void up();
    void down();
    void right();
    void left();

    bool is_valid_move(string);
    vector<Board> generate_children();

    int h(unordered_map<int, pair<int, int>>);
    void print();
};


#endif