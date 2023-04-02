#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
		item it3{"["+it1.to_string()+"]"};
		return cmp(it3, it2);
	}
	if (it2.type == 0) {
		item it3{"["+it2.to_string()+"]"};
		return cmp(it1, it3);
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	fstream in{"../P1/input.txt"};
	string line;

	vector<item> packets{};

	while (!in.eof()) {
		getline(in, line);
		if (line != "") {
			packets.push_back(item{line});
		}
	}

	packets.push_back(item{"[[2]]"});
	packets.push_back(item{"[[6]]"});

	sort(packets.begin(), packets.end(), [](item& a, item&b){ return cmp(a, b) == -1; });

	int res = 1;
	for (int i = 0; i < packets.size(); ++i)
		if (packets[i].to_string() == "[[2]]" || packets[i].to_string() == "[[6]]")
			res *= i + 1;

	cout << res << endl;

	return 0;
}