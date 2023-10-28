
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>

#include "graph_file.cpp"
#include "Node.h"
//#include "solve.cpp"



using namespace std;

#define m 10
#define n 10


void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void out_array(vector< vector<int> > vec)
{
    for (int i = 0; i < n; i++) // Цикл, который идёт по строкам
    {
        for (int j = 0; j < m; j++) // Цикл, который идёт по элементам
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

string pos_to_string(vector<vector<int>> pos) {
    string pos_str = "";
    for (auto p : pos) {
        pos_str += "[" + to_string(p[0]) + ", " + to_string(p[1]) + "]";
    }
    pos_str = '"' + pos_str + '"';
    return pos_str;
}

vector <Node> solve_tree() {
    vector <Node> Graph;
    vector<vector<int>> steps = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    vector<vector<int>> combos = {
        {0}, {1}, {2},
        {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1},
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0} };
    vector<vector<vector<int>>> nodes = { {{0, 0}, {0, 1}, {0, 2}} };
    vector<vector<int>> finish = { {3, 0}, {0, 4}, {4, 2} };
    vector<vector<int>> map = {
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0} };
    for (int q = 0; q < nodes.size(); q++) {
        vector<vector<int>> pos = nodes[q];
        string pos_str = pos_to_string(pos);
        cout << "pos: " << pos_str << endl;


        for (auto& combo : combos) {
            int agent = combo[0];
            for (auto& step : steps) {
                vector<vector<int>> node;
                for (int i = 0; i < pos.size(); i++) {
                    if (i == agent) {
                        if (-1 < (pos[i][0] + step[0]) && (pos[i][0] + step[0]) < 5 && -1 < (pos[i][1] + step[1]) && (pos[i][1] + step[1]) < 5 &&
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
                                if (-1 < (node[j][0] + step2[0]) && (node[j][0] + step2[0]) < 5 && -1 < (node[j][1] + step2[1]) && (node[j][1] + step2[1]) < 5 &&
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
                                        if (-1 < (node2[k][0] + step3[0]) && (node2[k][0] + step3[0]) < 5 && -1 < (node2[k][1] + step3[1]) && (node2[k][1] + step3[1]) < 5 &&
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
                                    this_node->name = node3_str;
                                    this_node->parent_name = pos_str;
                                    Graph.push_back(*this_node);
                                    if (node3 == finish) {
                                        cout << "finish" << endl;
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
                                this_node->name = node2_str;
                                this_node->parent_name = pos_str;
                                Graph.push_back(*this_node);
                                if (node2 == finish) {
                                    cout << "finish" << endl;
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
                        this_node->name = node_str;
                        this_node->parent_name = pos_str;
                        Graph.push_back(*this_node);
                        if (node == finish) {
                            cout << "finish" << endl;
                            return Graph;
                        }
                    }
                }
            }
        }
    }
    cout << "net puti blyat" << endl;
    return Graph;
}

int main()
{
	cout << "Hello Golubov!\n";



    vector < vector <int> > map(n, vector <int>(m));

    map = { 
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 4, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < n; i++)     // Цикл, который идёт по строкам
        for (int j = 0; j < m; j++) // Цикл, который идёт по элементам
        {
            //map[i][j] = 1;
        }

    out_array(map);

    cout << "\n";
    vector <Node> tree = solve_tree();

    

    /*
    vector <Node> Graph;

    for (int i = 0; i < 10; i++) {
        Node* this_node = new Node;
        this_node->name = to_string(i-1);
        this_node->parent_name = to_string(i);
        Graph.push_back(*this_node);
    }

    */

    graph_file graph;
    graph.create_file("graph.dot");
    graph.write_graph(tree);
    graph.gen_img();
    
    return 0;

}

