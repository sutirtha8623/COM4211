#include <iostream>
#include <vector>

using namespace std;

class Nqueens {
    int sol_count;
    int board_size;
    vector<int> solution_board;
public:
    Nqueens(int size) : board_size(size), sol_count(0) {}

    bool is_valid(vector<int> board, int row_idx) {
        for (int i =0; i < board.size(); i++) {
            if (row_idx == board[i]) return false;
        }
        int curr_index = board.size();
        for (int i = 0; i < board.size(); i++) {
            if (board[i] + (curr_index-i) == row_idx || board[i] - (curr_index-i) == row_idx) return false;
        }
        return true;
    }

    void print_board(vector<int> board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (j == board[i]) {
                    cout << "Q ";
                }
                else cout << "- ";
            }
            cout << endl;
        }
    }

    void search(vector<int> board, int curr_idx) {
        if (curr_idx == board_size) {
            print_board(board);
            sol_count++;
            cout << "Solution: " << sol_count << endl;
        }

        for (int i = 0; i < board_size; i++) {
            if (is_valid(board, i)) {
                board.push_back(i);
                search(board, curr_idx+1);
                board.pop_back();
            }
        }
    }

    void goal_search() {
        search(solution_board, 0);
    }

    void print_count() {
        cout << "Total solutions: " << sol_count << endl;
    }

};

int main() {
    Nqueens nq(15);
    nq.goal_search();
    nq.print_count();
}