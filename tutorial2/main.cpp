#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
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
        temp = temp->parent;
    } 
}

unordered_map<int, pair<int, int>> board_to_umap (Board b) {
    unordered_map<int, pair<int, int>> umap;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
    Board curr = start;
    start.g = 0;
    start.f = start.g + start.h(goal_map);
    fringe.push_back(start);
    while (!fringe.empty()) {
        sort(fringe.begin(), fringe.end(), compare_board);
        curr = fringe.back();
        if (curr == goal) {
            cout << "Found goal!" << endl;
            backtrack(curr, parents);
        }
        fringe.pop_back();
        auto children = curr.generate_children();
        for (auto child : children) {
            if (!in(child, fringe) && !(in(child, explored))) {
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

int main() {
    vector<int> goal = {1, 2 ,3, 4 ,5 ,6 ,7 ,8 ,9 ,10, 11, 12, 13, 14, 15, 0};
    vector<int> start = {1, 9, 2, 3, 5, 12, 11, 10, 13, 6 ,0 ,8 ,7 ,14, 15, 4};
    Board start_boa(start);
    Board goal_boa(goal);

    goal_search(start_boa, goal_boa);
}