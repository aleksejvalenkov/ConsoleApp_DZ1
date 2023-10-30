
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <ctime>

#include "graph_file.cpp"
#include "Node.h"
//#include "solve.cpp"

using namespace std;

void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void out_array(vector< vector<int> > vec)
{
    for (int i = 0; i < vec.size(); i++) // Цикл, который идёт по строкам
    {
        for (int j = 0; j < vec[0].size(); j++) // Цикл, который идёт по элементам
        {
            switch (vec[i][j])
            {
                case 1: {
                    SetColor(9, 0);
                    break;
                }
                case 0: {
                    SetColor(7, 0);
                    break;
                }
                case 4: {
                    SetColor(4, 0);
                    break;
                }
            }

            cout << vec[i][j] << ' '; // Вывод элементов i строки вектора
            SetColor(7, 0);
        }
        cout << endl;
    }
}

vector<vector<int>> input_pos_robots(string s) {
    vector<vector<int>> res = { {0, 0}, {0, 0}, {0, 0} };
    cout << "Input " + s + " cootrdinate the first robot" << endl;
    cin >> res[0][0] >> res[0][1];
    cout << "Input " + s + " cootrdinate the second robot" << endl;
    cin >> res[1][0] >> res[1][1];
    cout << "Input " + s + " cootrdinate the third robot" << endl;
    cin >> res[2][0] >> res[2][1];

    return res;
}

string pos_to_string(vector<vector<int>> pos) {
    string pos_str = "";
    for (auto p : pos) {
        pos_str += "[" + to_string(p[0]) + ", " + to_string(p[1]) + "]";
    }
    //pos_str = '"' + pos_str + '"';
    return pos_str;
}

vector <Node> generate_tree(vector<vector<int>> map, vector<vector<int>> start, vector<vector<int>> finish) {
    vector <Node> Graph;
    vector<vector<int>> steps = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    vector<vector<int>> combos = {
        {0}, {1}, {2},
        {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1},
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0} };

    vector<vector<vector<int>>> nodes = { start };


    for (int q = 0; q < nodes.size(); q++) {
        vector<vector<int>> pos = nodes[q];
        string pos_str = pos_to_string(pos);
        int parent_id = q;
        cout << "pos: " << pos_str << "\f node_id = " << parent_id << endl;


        for (auto& combo : combos) {
            int agent = combo[0];
            for (auto& step : steps) {
                vector<vector<int>> node;
                for (int i = 0; i < pos.size(); i++) {
                    if (i == agent) {
                        if (-1 < (pos[i][0] + step[0]) && (pos[i][0] + step[0]) < map.size() && -1 < (pos[i][1] + step[1]) && (pos[i][1] + step[1]) < map.size() &&
                            map[pos[i][0] + step[0]][pos[i][1] + step[1]] == 0 &&
                            find(pos.begin(), pos.end(), vector<int>{pos[i][0] + step[0], pos[i][1] + step[1]}) == pos.end()) {
                            node.push_back({ pos[i][0] + step[0], pos[i][1] + step[1] });
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        node.push_back(pos[i]);
                    }
                }
                if (combo.size() > 1) {
                    int agent2 = combo[1];
                    for (auto& step2 : steps) {
                        vector<vector<int>> node2;
                        for (int j = 0; j < node.size(); j++) {
                            if (j == agent2) {
                                if (-1 < (node[j][0] + step2[0]) && (node[j][0] + step2[0]) < map.size() && -1 < (node[j][1] + step2[1]) && (node[j][1] + step2[1]) < map.size() &&
                                    map[node[j][0] + step2[0]][node[j][1] + step2[1]] == 0 &&
                                    find(node.begin(), node.end(), vector<int>{node[j][0] + step2[0], node[j][1] + step2[1]}) == node.end()) {
                                    node2.push_back({ node[j][0] + step2[0], node[j][1] + step2[1] });
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                node2.push_back(node[j]);
                            }
                        }
                        if (combo.size() == 3) {
                            int agent3 = combo[2];
                            for (auto& step3 : steps) {
                                vector<vector<int>> node3;
                                for (int k = 0; k < node2.size(); k++) {
                                    if (k == agent3) {
                                        if (-1 < (node2[k][0] + step3[0]) && (node2[k][0] + step3[0]) < map.size() && -1 < (node2[k][1] + step3[1]) && (node2[k][1] + step3[1]) < map.size() &&
                                            map[node2[k][0] + step3[0]][node2[k][1] + step3[1]] == 0 &&
                                            find(node2.begin(), node2.end(), vector<int>{node2[k][0] + step3[0], node2[k][1] + step3[1]}) == node2.end()) {
                                            node3.push_back({ node2[k][0] + step3[0], node2[k][1] + step3[1] });
                                        }
                                        else {
                                            break;
                                        }
                                    }
                                    else {
                                        node3.push_back(node2[k]);
                                    }
                                }
                                if (node3.size() == 3 && find(nodes.begin(), nodes.end(), node3) == nodes.end()) {
                                    nodes.push_back(node3);
                                    string node3_str = pos_to_string(node3);
                                    Node* this_node = new Node;
                                    this_node->set_parent_id(parent_id);
                                    cout << "curr_node_per_id: \t" << parent_id << " curr_node_per - " << pos_str << " curr_node - " << node3_str << endl;
                                    this_node->name = node3_str;
                                    this_node->parent_name = pos_str;
                                    this_node->in_path = false;
                                    Graph.push_back(*this_node);
                                    if (node3 == finish) {
                                        cout << "Finish" << endl;
                                        return Graph;
                                    }
                                }
                            }
                        }
                        else {
                            if (node2.size() == 3 && find(nodes.begin(), nodes.end(), node2) == nodes.end()) {
                                nodes.push_back(node2);
                                string node2_str = pos_to_string(node2);
                                Node* this_node = new Node;
                                this_node->set_parent_id(parent_id);
                                cout << "curr_node_per_id: \t" << parent_id << " curr_node_per - " << pos_str << " curr_node - " << node2_str << endl;
                                this_node->name = node2_str;
                                this_node->parent_name = pos_str;
                                this_node->in_path = false;
                                Graph.push_back(*this_node);
                                if (node2 == finish) {
                                    cout << "Finish" << endl;
                                    return Graph;
                                }
                            }
                        }
                    }
                }
                else {
                    if (node.size() == 3 && find(nodes.begin(), nodes.end(), node) == nodes.end()) {
                        nodes.push_back(node);
                        string node_str = pos_to_string(node);
                        Node* this_node = new Node;
                        this_node->set_parent_id(parent_id);
                        cout << "curr_node_per_id: \t" << parent_id << " curr_node_per - " << pos_str << " curr_node - " << node_str << endl;
                        this_node->name = node_str;
                        this_node->parent_name = pos_str;
                        this_node->in_path = false;
                        Graph.push_back(*this_node);
                        if (node == finish) {
                            cout << "Finish" << endl;
                            return Graph;
                        }
                    }
                }
            }
        }
    }
    cout << "Path not found: maybe it doesn't exist" << endl;
    return Graph;
}

vector <Node> solve_tree(vector <Node> tree) {
    cout << "final path \t" << tree[tree.size() - 1].name << endl;
    //cout << "fin node id= " << tree.size() - 1 << endl;
    Node current_node = tree[tree.size() - 1];
    tree[tree.size() - 1].in_path = true;
    while (current_node.parent_node_id != 0) {
        cout << "Step      \t" << tree[current_node.parent_node_id - 1].name << endl;
        //cout << "current_node_per_id= " << current_node.parent_node_id << endl;
        tree[current_node.parent_node_id - 1].in_path = true;
        current_node = tree[current_node.parent_node_id];
    }
    cout << "Start     \t" << current_node.parent_name << endl;
    return tree;
}

int main()
{
    /*
    vector<vector<int>> map = {
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0} };
        */
    
    vector<vector<int>> map = { 
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
    };
    
    out_array(map);

    //vector<vector<int>> start = { {0, 1}, {0, 2}, {0, 3} };
    //vector<vector<int>> finish = { {1, 1}, {3, 2}, {1, 3} };

    vector<vector<int>> start = input_pos_robots("Start");
    vector<vector<int>> finish = input_pos_robots("Finish");

    cout << "Start" << pos_to_string(start) << endl;
    cout << "Finish" << pos_to_string(finish) << endl;

    cout << "\n";
    unsigned int start_time = clock(); // начальное время
    vector <Node> tree = generate_tree(map, start, finish);

    vector <Node> path = solve_tree(tree);

    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    cout << "WORK TIME in ms: " << search_time << endl;
    
    graph_file graph;
    graph.create_file("graph.dot");
    graph.write_graph(path);
    graph.gen_img();

    system("pause");
    return 0;

}

