#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// string get_item(const char* c) {
// 	string res = "";
// }

class item {
public:
	int type;
	int self;
	vector<item> content;

	item (string s) {
		// cout << "New item: " << s << " (type: " << (s[0] == '[' ? "list" : "number") << ")\n";
		if (s[0] == '[') {
			type = 1;
			for (int i = 1; i < s.size() - 1; ++i) {
				string tok = "";
				int left = 0, right = 0;
				while (i < s.size() - 1 && !(s[i] == ',' && left == right)) {
					tok += s[i];
					if (s[i] == '[')
						++left;
					if (s[i] == ']')
						++right;
					++i;
				}
				content.push_back(item{tok});
			}
		} else {
			type = 0;
			self = stoi(s);
		}
	}

	string to_string() {
		if (type == 0)
			return std::to_string(self);
		string res = "[";
		for (item i : content){
			res += i.to_string();
			res += ",";
		}
		if (content.size())
			res.pop_back();
		res += "]";
		return res;
	}
};

int cmp(item& it1, item& it2) {
	// cout << "Comparing " << it1.to_string() << " and " << it2.to_string() << endl;
	if (it1.type == 0 && it2.type == 0) {
		if (it1.self < it2.self)
			return -1;
		if (it1.self > it2.self)
			return 1;
		return 0;
	}
	if (it1.type == 1 && it2.type == 1) {
		int min_size = min(it1.content.size(), it2.content.size());
		for (int i = 0; i < min_size; ++i) {
			int part_cmp = cmp(it1.content[i], it2.content[i]);
			if (part_cmp != 0)
				return part_cmp;
		}
		if (it2.content.size() > min_size)
			return -1;
		if (it1.content.size() > min_size)
			return 1;
		return 0;
	}
	if (it1.type == 0) {
		it1.type = 1;
		it1.content.push_back(item{to_string(it1.self)});
		return cmp(it1, it2);
	}
	if (it2.type == 0) {
		it2.type = 1;
		it2.content.push_back(item{to_string(it2.self)});
		return cmp(it1, it2);
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};

	string item1, item2, dummy;
	int pos = 1;
	int res = 0;
	while (!in.eof()) {
		getline(in, item1);
		getline(in, item2);
		getline(in, dummy);
		item it1{item1}, it2{item2};
		if (cmp(it1, it2) == -1)
			res += pos;
		++pos;
	}

	cout << res << endl;

	return 0;
}