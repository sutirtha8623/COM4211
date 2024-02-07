#include <iostream>
#include <array>
#include <vector>
using namespace std;

//because it is too cumbersome to access elements in std::tuple
class Tuple {
public:
    //missionaries, cannibals boat
    int m, c, b;

    Tuple(int m, int c, int b) : m(m), c(c), b(b) {}

    Tuple operator+(const Tuple& pt) {
        return Tuple(this->m + pt.m, this->c + pt.c, this->b + pt.b);
    }

    Tuple operator-(const Tuple& pt) {
        return Tuple(this->m - pt.m, this->c - pt.c, this->b - pt.b);
    }

    bool operator==(const Tuple& t) {
        return (this->m == t.m && this->c == t.c && this->b == t.b);
    }

    bool operator!=(const Tuple& t) {
        return !(*this == t);
    }

    friend ostream& operator<< (ostream& os, const Tuple& t) {
        os << "(" << t.m << ", " << t.c << ", " << t.b << ")";
        return os;
    }
};

class State {
    Tuple state;
    State* parent;
public:
    State(Tuple s) : state(s) {parent = nullptr;}
    State(Tuple s, State* p) : state(s), parent(p) {}

    State* get_parent() {return parent;}
    Tuple get_state() {return state;}

    bool is_valid() {
        if ((state.m >= 0 && state.m <= 3) && (state.c >= 0 && state.c <= 3) && 
        (state.m == 0 || state.m >= state.c) && (state.m == 3 || state.m <= state.c)) {
            return true;
        }
        return false;
    }

    State perform_action(Tuple action, char signum) {
        if (signum == '+') {
            Tuple child = state + action;
            State* parent = this;
            return State(child, parent);
        }
        else {
            Tuple child = state - action;
            State* parent = this;
            return State(child, parent);
        }
    }

    bool check_goal() {
        return (state == Tuple(0, 0, 0));
    }

    bool in(vector<State> list) {
        for (auto i : list) {
            if (state == i.state) {
                return true;
            }
        }
        return false;
    }

    void print_path() {
        State* curr = this;
        for (int i = 0; i < 11; i++) {
            cout << curr->state << "<- ";
            curr = curr->parent;
        }
        cout << endl;
    }

};

vector<Tuple> action_set = {Tuple(1, 0, 1), Tuple(2, 0, 1), Tuple(0, 1, 1), Tuple(0, 2, 1), Tuple(1, 1, 1)};
vector<State> frontier;
vector<State> explored;
void BFS(State init) {
    if (init.check_goal()) {
        cout << "Found goal!\n";
        return;
    }
    
    frontier.push_back(init);
    
    char curr_sign = '-';
    int level = 0;

    while (true) {
        cout << endl <<"Level: " << level << endl;
        if (frontier.empty()) {
            cout << "Failure!";
            return;
        }
        State curr = frontier.back();
        frontier.pop_back();
        explored.push_back(curr);

        for (auto i : action_set) {
            auto child = curr.perform_action(i, curr_sign);
            if (!child.is_valid()) {
                continue;
            }
        
            if (!child.in(explored) && !child.in(frontier)) {
                cout << "Exploring "<< child.get_state() << endl;
                if (child.check_goal()) {
                    cout << "Found goal!" << endl;
                    child.print_path();
                    return;
                }
                frontier.push_back(child);
            }
        }
        level++;
        curr_sign == '-' ? curr_sign = '+' : curr_sign = '-';
    }
}

int main() {
    Tuple init(3, 3, 1);
    State initstate(init);
    BFS(initstate);
}