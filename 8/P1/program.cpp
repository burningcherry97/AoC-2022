#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	fstream in{"input.txt"};
	vector<string> map;

	while (!in.eof()) {
		map.push_back("");
		getline(in, map.back());
	}


	set<pair<int,int>> visibles{};

	int rows = map.size();
	int columns = map[0].size();

	for (int i = 0; i < rows; ++i) {
		char height = 0;
		for (int j = 0; j < columns; ++j) {
			if (height < map[i][j]) {
				height = map[i][j];
				visibles.insert(make_pair(i,j));
			}
		}
		height = 0;
		for (int j = columns-1; j >= 0; --j) {
			if (height < map[i][j]) {
				height = map[i][j];
				visibles.insert(make_pair(i,j));
			}
		}
	}
	for (int i = 0; i < columns; ++i) {
		char height = 0;
		for (int j = 0; j < rows; ++j) {
			if (height < map[j][i]) {
				height = map[j][i];
				visibles.insert(make_pair(j,i));
			}
		}
		height = 0;
		for (int j = rows-1; j >= 0; --j) {
			if (height < map[j][i]) {
				height = map[j][i];
				visibles.insert(make_pair(j,i));
			}
		}
	}

	cout << visibles.size() << endl;

	return 0;
}