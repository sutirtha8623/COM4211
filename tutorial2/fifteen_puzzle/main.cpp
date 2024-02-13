#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>
#include "board.hpp"

bool compare_board(Board b1, Board b2) {
    return b1.f > b2.f;
}

bool in(Board& b, vector<Board> b_vec) {
    for (int i = 0; i < b_vec.size(); i++) {
        if (b == b_vec[i]) return true;
    }
    return false;
}

void backtrack(Board current, vector<Board>& parents) {
    Board* temp = &current;
    while(temp != nullptr) {
        parents.push_back(*temp);
        // cout << endl;
        temp = temp->parent;
    } 
}

unordered_map<int, pair<int, int>> board_to_umap (Board b) {
    unordered_map<int, pair<int, int>> umap;
    for (int i = 0; i < b.n; i++) {
        for (int j = 0; j < b.n; j++) {
            umap[b.data[i][j]] = make_pair(i, j);
        }
    }
    return umap;
}

vector<Board> parents;
void goal_search(Board start, Board goal) {
    unordered_map<int, pair<int, int>> goal_map = board_to_umap(goal);
    vector<Board> fringe;
    vector<Board> explored;
    
    start.g = 0;
    start.f = start.g + start.h(goal_map);
    start.parent = nullptr;
    Board curr = start;
    fringe.push_back(start);
    while (!fringe.empty()) {
        sort(fringe.begin(), fringe.end(), compare_board);
        curr = fringe.back();
        fringe.pop_back();
        // cout << curr.g << endl;
        if (curr == goal) {
            cout << "Found goal!" << endl;
            backtrack(curr, parents);
            return;
        }

        auto children = curr.generate_children();

        for (auto child : children) {
            if (!in(child, fringe) && !(in(child, explored))) {
                // cout << "Exploring: " << endl;
                // child.print();
                child.g = curr.g + 1;
                child.f = child.g + child.h(goal_map);
                Board* p = new Board(curr);
                child.parent = p;
                fringe.push_back(child);
            }
        }
        explored.push_back(curr);
    }
    cout << "Failure!" << endl;
    return;
}

vector<int> input(vector<int> p) {
    int t;
    for (int i = 0; i < p.size(); i++) {
        cin >> t;
        p[i] = t;
    }
    return p;
}

int main() {
    cout << "Enter the value of n: ";
    int size;
    cin >> size;
    vector<int> start (size*size);
    vector<int> goal (size*size);
    cout << "Please enter the elements of the starting matrix in a single line and separated by a space, represent the blank with a zero: ";
    start = input(start);
    cout << "Please enter the elements of the goal matrix in a single line and separated by a space, represent the blank with a zero: ";
    goal = input(goal);

    Board start_boa(start, size);
    Board goal_boa(goal, size);

    
    goal_search(start_boa, goal_boa);
    cout << "Path: " << endl;
    for (int i = parents.size() - 1; i >= 0; i--) {
        parents[i].print();
        // if (i != 0) cout << " --> " << endl;
    }
    cout << endl;
}