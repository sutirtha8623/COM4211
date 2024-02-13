#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/copy.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <string>
using namespace std;
using namespace boost;


typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;


int calculate_h(Graph g, vector<int> path) {
    auto cost = get(boost::edge_weight, g);
    vector<Edge> MST;
    Graph g_copy;
    copy_graph(g, g_copy);
    for (int i = 1; i < path.size(); i++) {
        clear_vertex(i, g_copy);
        remove_vertex(i, g_copy);
    }
    kruskal_minimum_spanning_tree(g_copy, back_inserter(MST));

    int h = 0;
    for (auto e : MST) {
        h += cost[e];
    }
    return h;
}

struct State {
    vector<int> tour;
    int f;
    State(vector<int> v) : tour(v){};
    friend ostream& operator<< (ostream& os, const State& s) {
        os << "{";
        for (auto i : s.tour) {
            os << i << ", ";
        }
        os << "}";
        return  os;
    }
};

bool state_comparator(State s1, State s2) {
    return s1.f > s2.f;
}

vector<int> goal_search(Graph g, int init) {
    vector<State> frontier;
    int num = num_vertices(g);
    int curr_g = 0;

    vector<int> current_tour;
    current_tour.push_back(init);
    State start(current_tour);
    start.f = calculate_h(g, {});
    frontier.push_back(start);

    while(!frontier.empty()) {
        sort(frontier.begin(), frontier.end(), state_comparator);
        auto current_state = frontier.back();
        frontier.pop_back();

        if (current_state.tour.size() == num) {
            return current_tour;
        }
    
        graph_traits<Graph>::adjacency_iterator ai, ai_end;
        for (tie(ai, ai_end) = adjacent_vertices(current_tour.back(), g); ai != ai_end; ++ai) {
            WeightMap weight_map = get(edge_weight, g);
            int next_vertex = *ai;
            if (find(current_tour.begin(), current_tour.end(), next_vertex) == current_tour.end()) {
                // cout << "foo" << endl; 
                Vertex v1 = vertex(current_tour.back(), g);
                Vertex v2 = vertex(next_vertex, g);
                Edge e;
                bool exists;
                tie(e, exists) = edge(v1, v2, g);

                curr_g = curr_g + get(weight_map, e);
                vector<int> next_tour = current_tour;
                next_tour.push_back(next_vertex);
                current_tour = next_tour;
                State next(next_tour);
                int cost = curr_g + calculate_h(g, current_tour);
                next.f = cost;
                frontier.push_back(next);
            }
            // cout << "{";
            // for(auto i : frontier) {
            //     cout << i << ", " << endl;
            // }
            // cout << "}" << endl;
        }
    }
}


int main()
{
    Graph g(3); // 0..2

    add_edge(0, 1, {1}, g);
    add_edge(0, 2, {8}, g);
    add_edge(0, 3, {2}, g);
    add_edge(1, 2, {4}, g);
    add_edge(1, 3, {9}, g);
    add_edge(2, 3, {3}, g);

    // vector<int> v = {0, 1};

    // cout << calculate_h(g, v) << endl;

    vector<int> tour = goal_search(g, 0);
    for (auto i : tour) {
        cout << i;
    }
    cout << endl;

    // auto cost = get(boost::edge_weight, g);
    // std::vector<Edge> spanning_tree;
    // kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));


    // std::cout << "MST Solution:\n";
    // for (auto e : spanning_tree) {
    //     std::cout << e << ": " << cost[e] << "\n";
    // }

    
}