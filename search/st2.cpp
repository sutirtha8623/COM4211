#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

map<pair<string, string>, int> MC;
int CC = 0;
vector<string> V;
int n;
int k;

void generate_combinations(const vector<int>& arr, int r, vector<int>& combination, int index, int start, vector<vector<int>>& result) {
    if (index == r) {
        result.push_back(combination);
        return;
    }

    for (int i = start; i < arr.size(); ++i) {
        combination[index] = arr[i];
        generate_combinations(arr, r, combination, index + 1, i + 1, result);
    }
}

vector<vector<int>> generate_all_combinations(const vector<int>& arr, int r) {
    vector<vector<int>> result;
    vector<int> combination(r);

    generate_combinations(arr, r, combination, 0, 0, result);

    return result;
}

struct Node {
    vector<string> strings;
    int path_cost;
    int total_cost;
    int position;
    Node* parent;
    int h;

    Node (vector<string> s, int pc, int tc, int pos, Node* p, int heu=0) : 
    strings(s), path_cost(pc), total_cost(tc), position(pos), parent(p), h(heu) {}

    bool check_goal();
    bool check_strings();
    int new_pos_cost(string);
    string generate_pos_string(int);
    int generate_total_cost();

    vector<string> reconstruct_strings(int, string);
    int calculate_h();

    vector<Node> generate_children(int);

};

bool Node::check_goal() {
    return (position == n-1);
}

bool Node::check_strings() {
    for (auto i : strings) {
        if (i.length() != n) return false;
    }
    return true;
}

int Node::new_pos_cost(string pos_string) {
    int cost = 0;
    int len = pos_string.length();
    for (int i = 0; i < len - 1; i++) {
        for (int j = i+1; j < len; j++) {
            cost += MC[make_pair(to_string(pos_string[i]), to_string(pos_string[j]))];
        }
    }
    return cost;
}

string Node::generate_pos_string(int pos) {
    string s = "";
    for (auto i : strings) {
        s += i[pos];
    }
    return s;
}

int Node::generate_total_cost() {
    int cost = 0;
    for (auto i : strings) {
        for (auto j : i) {
            if (j == '-') cost += CC;
        }
    }
    for (int i = 0; i < n; i++) {
        string pos_string = generate_pos_string(i);
        cost += new_pos_cost(pos_string);
    }
    
    return cost;
}

vector<string> Node::reconstruct_strings(int pos, string s) {
    vector<string> new_strings;

    for (int i = 0; i < strings.size(); i++) {
        if (s[i] == '-') {
            string temp = strings[i].substr(0, pos) + "-" + strings[i].substr(pos, strings[i].length() - pos);
            new_strings.push_back(temp);
        }
        else {
            new_strings.push_back(strings[i]);
        }
    }
    return new_strings;
}

int Node::calculate_h() {
    int cost = 0;
    for (auto i : strings) {
        for (auto j : i) {
            if (j == '-') cost += CC;
        }
    }

    return cost;
}

vector<Node> Node::generate_children(int pos) {
    vector<string> children;
    vector<Node> states;
    bool flag = true;
    string pos_string = generate_pos_string(pos);
    for (auto i : strings) {
        if (i.length() < pos) flag = false;
    }

    if (flag == true) {
        vector<int> range;
        for (int i = 0; i < strings.size(); i++) {
            range.push_back(i);
        }

        for (int dc = 0; dc <= strings.size(); dc++) {
            for (auto i : generate_all_combinations(range, dc)) {
                string temp_pos_string(pos_string);
                for (auto j : i) {
                    
                    temp_pos_string[j] = '-';
                }
                children.push_back(temp_pos_string);
            }
        }
        for (auto s : children) {
            auto temp_strings = reconstruct_strings(pos, s);
            auto temp_pos_cost = new_pos_cost(s);
            auto temp_total_cost = total_cost + temp_pos_cost;

            bool temp_flag = true;
            for (auto i : temp_strings) {
                if (i.length() > n) temp_flag = false;
            }

            if (temp_flag == true) {
                states.push_back(Node(temp_strings, temp_pos_cost, temp_total_cost, pos+1, nullptr));

            }
        }
    }
    return states;
}

Node search(vector<string> strings) {
    Node root(strings, 0, 0, 0, nullptr);
    vector<Node> fringe;
    fringe.push_back(root);
    vector<Node> explored;

    Node optimal(strings, 50000,50000, 0, nullptr, 50000);

    while (!fringe.empty()) {
        Node curr = fringe.back();
        fringe.pop_back();

        if (curr.check_goal() || curr.check_strings()) {
            if (curr.check_strings()) {
                curr.h = curr.generate_total_cost();
            }
            if (curr.total_cost == 0 || curr.h < optimal.h) {
                optimal = curr;
            }
        }
        else {
            auto children = curr.generate_children(curr.position);
            for (auto child : children) {
                child.parent = &curr;
                child.h = child.calculate_h();
                fringe.push_back(child);
            }
            sort(fringe.begin(), fringe.end(), [] (Node a, Node b) {return a.h > b.h;});
            explored.push_back(curr);
        }
    }
    return optimal;
}

string read_file_into_string (std::string fileName) {
    ifstream input_file(fileName);
    ostringstream osstr;
    osstr << input_file.rdbuf();
    return osstr.str();
}

vector<string> separate_by_nl(string s) {
    vector<string> result;
    string temp = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\n') {
            result.push_back(temp);
            temp = "";
            continue;
        }
        temp += s[i];
    }
    return result;
}

int main() {
    vector<string> file_strs = separate_by_nl(read_file_into_string("input.txt"));

    int v_n = stoi(file_strs[0]);
    // cout << v_n;;

    string V_str = file_strs[1];

    size_t pos = 0;
    string delimiter = ", ";
    while ((pos = V_str.find(delimiter)) != string::npos) {
        V.push_back(V_str.substr(0, pos));
        V_str.erase(0, pos + delimiter.length());
    }
    V.push_back(V_str);

    // cout << V[0] << endl;

    k = stoi(file_strs[2]);

    vector<string> X(k);
    for (int i = 0; i < k; ++i) {
        X[i] = file_strs[i+3];
    }

    // cout << X[0] << endl;

    CC = stoi(file_strs[6]);
    // cout << CC << endl;
    for (int i = 0; i < V.size(); i++) {
        string line = file_strs[i+7];
        // cout << line << endl;
        // cout << line[0] << endl;
        int j;
        for (j = i; j < V.size(); j++) {
            // cout << line[2*j] << endl;
            MC[make_pair(V[i], V[j])] = MC[make_pair(V[j], V[i])] = stoi(to_string(line[2*j])) - 48;
            // cout << MC[make_pair(V[i], V[j])] << endl;
        }
        MC[make_pair(V[i], "-")] = MC[make_pair("-", V[i])] = stoi(to_string(line[2*j])) - 48;
        // cout << MC[make_pair(V[i], "-")] << endl;
    }

    string line = file_strs[11];
    MC[make_pair("-", "-")] = stoi(to_string(line.back()));
    // cout << MC[make_pair("-", "-")] << endl;

    n = 0;
    for (auto i : X) {
        if (i.length() >= n) {
            n = i.length();
        }
    }

    auto sol = search(X);

    ofstream out_file("output.txt");
    if (!out_file.is_open()) {
        cerr << "Error: Unable to open output file!" << endl;
        return 1;
    }

    for (const auto& i : sol.strings) {
        out_file << i << '\n';
    }

    out_file.close();

    ifstream out_file_read("output.txt");
    if (!out_file_read.is_open()) {
        cerr << "Error: Unable to open output file for reading!" << endl;
        return 1;
    }

    string output_line;
    while (getline(out_file_read, output_line)) {
        cout << output_line << endl;
    }

    return 0;
}