#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	int parent_node_id = 0;
	int id;
	string parent_name;
	string name;
	int level;
	bool in_path;

	int get_parent_id() {
		return parent_node_id;
	}

	void set_parent_id(int id) {
		parent_node_id = id;
	}
};

