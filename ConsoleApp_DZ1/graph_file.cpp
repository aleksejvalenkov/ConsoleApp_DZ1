
#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"



using namespace std;

class graph_file {
private:
    ofstream file;

public:
    void create_file(string file_name){
        file.open(file_name);
        if (file) {
            cout << "Open file\n";
        }
        else
        {
            cout << "Not open!";
        }
    }

    void write_graph(vector <Node> graph) {
        file << "digraph test{" << endl;
        for (int i = 0; i < graph.size(); i++) {
            string p_id = to_string(graph[i].parent_node_id);
            string sourse = '"' + graph[i].name + '"';
            string target = '"' + graph[i].parent_name + '"';
            string edge;
            cout << graph[i].in_path << endl;
            if (graph[i].in_path) {
                edge = target + " -> " + sourse + "[color=" + '"' + "blue" + '"' + "]";
                file << target + "[color=" + '"' + "blue" + '"' + "]" << endl;
                file << sourse + "[color=" + '"' + "blue" + '"' + "]" << endl;
            }
            else {
                edge = target + " -> " + sourse;
            }
            file << edge << endl;
        }

        file << "}" << endl;
        file.close();
    }

    void gen_img() {
        cout << "Generate image" << endl;
        system("dot -Tpdf -O graph.dot");
    }
};
