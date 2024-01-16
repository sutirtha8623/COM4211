#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a class Nqueens to encapsulate the N-Queens problem solution
class Nqueens {
    int sol_count;                 // Counter for the total number of solutions
    int board_size;                // Size of the chessboard (number of queens)
    vector<int> solution_board;    // Vector to store the current solution configuration

public:
    // Constructor to initialize the board size and solution count
    Nqueens(int size) : board_size(size), sol_count(0) {}

    // Check if placing a queen in the current row (row_idx) is a valid move
    bool is_valid(vector<int> board, int row_idx) {
        for (int i = 0; i < board.size(); i++) {
            // Check if there is already a queen in the same row
            if (row_idx == board[i])
                return false;

            // Check diagonally for queens in the same line of attack
            int curr_index = board.size();
            if (board[i] + (curr_index - i) == row_idx || board[i] - (curr_index - i) == row_idx)
                return false;
        }
        return true;
    }

    // Print the current chessboard configuration
    void print_board(vector<int> board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (j == board[i]) {
                    cout << "Q ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
    }

    // Recursive function to search for solutions using backtracking
    void search(vector<int> board, int curr_idx) {
        if (curr_idx == board_size) {
            // If all queens are placed, print the solution and update the solution count
            print_board(board);
            sol_count++;
            cout << "Solution: " << sol_count << endl;
        }

        // Try placing a queen in each column of the current row
        for (int i = 0; i < board_size; i++) {
            if (is_valid(board, i)) {
                // If placing a queen is valid, update the board and move to the next row
                board.push_back(i);
                search(board, curr_idx + 1);
                board.pop_back();  // Backtrack by removing the last queen placement
            }
        }
    }

    // Function to initiate the search for solutions
    void goal_search() {
        search(solution_board, 0);
    }

    // Print the total number of solutions found
    void print_count() {
        cout << "Total solutions: " << sol_count << endl;
    }
};

// Main function
int main(int argc, char** argv) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        cout << "Usage: executable board_size\n";
        return 1;
    }

    // Create an instance of the Nqueens class with the specified board size
    Nqueens nq(stoi(argv[1]));

    // Initiate the search for solutions
    nq.goal_search();

    // Print the total number of solutions found
    nq.print_count();

    return 0;
}
