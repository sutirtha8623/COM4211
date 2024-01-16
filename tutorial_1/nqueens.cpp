#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Board {
    int size;
    vector<int> queens;
public:
    Board(int s) : size(s) {queens.resize(size, -1);}

    void add_queen(int col_idx, int row_idx) {
        queens[col_idx] = row_idx;
    }

    void set_board(vector<int> b) {
        for (int i = 0; i < size; i++) {
            queens[i] = b[i];
        }
    }

    vector<int> get_queens() {
        return queens;
    }

    void print_board() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (j == queens[i]) {
                    cout << "Q ";
                }
                else cout << "* ";
            }
            cout << endl;
        }
    }

    int get_size() {
        return size;
    }
};

class Nqueens {
    int board_size;
public:
    Nqueens(Board board){
        board_size = board.get_size();
    }

    bool is_viable(Board board, int new_row_idx) {
        vector<int> queens = board.get_queens();
        if (find(queens.begin(), queens.end(), new_row_idx) != queens.end()) return false;
        for (int i = 0; i < board_size; i++) {
            if (queens[i] + (board_size - i) == new_row_idx || queens[i] - (board_size - i) == new_row_idx) return false;
        }
        return true;
    }

    void goal_search(Board board, int curr_idx) {
        if (curr_idx == board_size) {
            cout << "foo";
            board.print_board();
            exit(0);
        }
        
        for (int i = 0; i < board_size; i++) {
            if (is_viable(board, i)) {
                board.add_queen(curr_idx, i);
                goal_search(board, curr_idx+1);
                board.add_queen(curr_idx, -1);
            }
        }
    }
};

int main() {
    Board board(8);
    Nqueens nqueens(board);
    nqueens.goal_search(board, 0);
}