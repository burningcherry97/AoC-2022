#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class element {
public:
	string name;
	int type;
	int size;
	element* parent;
	vector<element*> members;

	void set_size() {
		int res = 0;
		for (element* el : members) {
			if (el->type == 1)
				el->set_size();
			res += el->size;
		}
		size = res;
	}

	int prune_size(int breakaway) {
		int res = 0;
		for (element* el : members)
			if (el->type == 1) {
				if (el->size < breakaway) {
					res += el->size;
				}
				res += el->prune_size(breakaway);
			}
		return res;
	}

	element(string name, int type, int size, element* parent) {
		this->name = name;
		this->type = type;
		this->size = size;
		this->parent = parent;
	}

	friend ostream& operator<<(ostream& out, element* el) {
		out << '{' << el->name << ' ' << el->size << ' ' << (el->type ? "folder" : "file");
		for (element* el : el->members)
			out << el;
		return out << '}';
	}
};

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};
	string arg1, arg2, arg3;

	element* filesystem = new element("/",1,0,nullptr);
	element* ptr = filesystem;

	while (!in.eof()) {
		in >> arg1;
		if (arg1 == "$") {
			in >> arg2;
			if (arg2 == "cd") {
				in >> arg3;
				if (arg3 == "/")
					ptr = filesystem;
				else if (arg3 == "..")
					ptr = ptr->parent;
				else
					for (element* el : ptr->members)
						if (el->name == arg3) {
							ptr = el;
							break;
						}
			} else if (arg2 == "ls") {
				;
			}
		} else if (arg1 == "dir") {
			in >> arg2;
			ptr->members.push_back(new element(arg2,1,0,ptr));
		} else {
			istringstream iss{arg1};
			int size;
			iss >> size;
			in >> arg2;
			ptr->members.push_back(new element(arg2,0,size,ptr));
		}
	}

	filesystem->set_size();
	cout << filesystem->prune_size(100000) << endl;

	return 0;
}