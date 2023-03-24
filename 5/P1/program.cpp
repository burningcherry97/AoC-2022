#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};
	string line;
	vector<string> cargo{};

	while (getline(in, line)) {
		if (line[1] == '1') {
			getline(in, line);
			break;
		}

		for (int i = 0; i < (line.size() + 1)/4; ++i) {
			char c = line[4*i + 1];
			if (c != ' ') {
				if (cargo.size() < i + 1)
					cargo.resize(i + 1);
				cargo[i] += c;
			}
		}
	}

	for (string& s : cargo)
		reverse(s.begin(), s.end());

	while (getline(in, line)) {
		istringstream iss{line};
		string dummy;
		int amount, source, target;
		iss >> dummy >> amount >> dummy >> source >> dummy >> target;
		--source; --target;
		for (int i = 0; i < amount; ++i) {
			cargo[target] += cargo[source].back();
			cargo[source].pop_back();
		}
	}

	for (string s : cargo)
		cout << s.back();
	cout << endl;

	return 0;
}