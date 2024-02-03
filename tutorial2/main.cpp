#include <iostream>
#include <vector>
#include "board.hpp"

int main() {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    Board board(vec);
    board.print();
    Board c(board);
    c.up();
    cout << endl;
    c.print();
    cout << endl;
    board.print();
}